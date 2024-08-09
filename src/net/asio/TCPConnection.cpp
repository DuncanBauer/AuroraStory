#include "TCPConnection.h"
#include "constants/CryptoConstants.h"
#include "net/packets/PacketCreator.h"
#include "util/MapleAESOFB.h"
#include "util/PacketTool.h"

namespace net
{
    TCPConnection::TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets)
        : m_socket(std::move(socket)),
          m_incomingPacketServerQueue(incomingPackets),
          m_ivRecv(Constants::Crypto::k_ivBufferSize),
          m_ivSend(Constants::Crypto::k_ivBufferSize)
    {
    }

    TCPConnection::~TCPConnection()
    {
        disconnect();
    }

    // Connect to client
    void TCPConnection::connect(TCPServerInterface* server, u32 uid)
    {
        if (m_socket.is_open())
        {
            Packet packet = PacketCreator::getHandshake(m_ivRecv, m_ivSend);

            // start an async read operation to receive the header of the next packet
            asio::async_write(m_socket,
                              asio::buffer(packet.data(), packet.size()),
                              std::bind(&TCPConnection::writeHandler,
                                        shared_from_this(),
                                        std::placeholders::_1,
                                        std::placeholders::_2));

            readPacket();
        }
    }

    void TCPConnection::disconnect()
    {
        if (isConnected())
        {
            m_socket.close();
        }
    }

    bool TCPConnection::isConnected()
    {
        return m_socket.is_open();
    }

    void TCPConnection::readPacket()
    {
        m_tempIncomingPacket.reset(new Packet(4));

        // start an async read operation to receive the header of the next packet
        asio::async_read(m_socket,
                         asio::buffer(m_tempIncomingPacket.get()->data(), 4),
                         std::bind(&TCPConnection::readHeaderHandler,
                                   shared_from_this(),
                                   std::placeholders::_1,
                                   std::placeholders::_2));
    }

    void TCPConnection::readHeaderHandler(const std::error_code& ec, std::size_t bytesTransferred)
    {
        if (!ec)
        {
            // get the packet length from the header buffer
            u16 packetLength = util::MapleAESOFB::getPacketLength(m_tempIncomingPacket.get()->data());

            // a packet must consist of 2 bytes atleast
            if (packetLength < 2)
            {
                disconnect();
                return;
            }

            // receive the data
            m_tempIncomingPacket.reset(new Packet(packetLength));

            // start an async read operation to receive the rest of the packet
            asio::async_read(m_socket,
                             asio::buffer(m_tempIncomingPacket.get()->data(), packetLength),
                             std::bind(&TCPConnection::readBodyHandler,
                                       shared_from_this(),
                                       std::placeholders::_1,
                                       std::placeholders::_2));
        }
        else
        {
            SERVER_WARN("[{}] Read Header Fail.", m_socket.remote_endpoint().address().to_string());
            SERVER_WARN(ec.message());
            disconnect();
        }
    }

    void TCPConnection::readBodyHandler(const std::error_code& ec, std::size_t bytesTransferred)
    {
        if (!ec)
        {
            // get the packet length
            u16 bytesAmount = static_cast<u16>(bytesTransferred);

            // decrypt the packet
            util::MapleAESOFB::decrypt(m_tempIncomingPacket.get()->data(), m_ivRecv.data(), bytesAmount);

            processPacket(*m_tempIncomingPacket.get());

            // start an async read operation to receive the header of the next packet
            readPacket();
        }
        else
        {
            SERVER_WARN("[{}] Read Body Fail.", m_socket.remote_endpoint().address().to_string());
            SERVER_WARN(ec.message());
            disconnect();
        }
    }

    void TCPConnection::send(const Packet& packet)
    {
        Packet header(4);
        Packet body = packet;
        Packet outgoingPacketBuffer(body.size() + 4);

        // Create packet header
        util::MapleAESOFB::createPacketHeader(header.data(), m_ivSend.data(), (u16)body.size());

        // Encrypt packet
        util::MapleAESOFB::encrypt(body.data(), m_ivSend.data(), (u16)body.size());

        // Move packet bytes to new buffer
        std::copy(header.begin(), header.end(), outgoingPacketBuffer.begin());
        std::copy(body.begin(), body.end(), outgoingPacketBuffer.begin() + 4);

        // Write the packet
        asio::async_write(m_socket,
                          asio::buffer(outgoingPacketBuffer.data(), body.size() + 4),
                          std::bind(&TCPConnection::writeHandler,
                                    shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));
    }

    void TCPConnection::writeHandler(const std::error_code& ec, std::size_t bytesTransferred)
    {
        if (!ec)
        {
            // Remove the packet from the outgoing queue and see if there's any more to send, if so write the next packet
            if (m_outgoingPacketQueue.empty())
            {
                return;
            }
        }
        else
        {
            SERVER_WARN("[{}] Write Packet Fail.", m_socket.remote_endpoint().address().to_string());
            SERVER_WARN(ec.message());
            disconnect();
        }
    }
}