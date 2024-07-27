#include "TCPConnection.h"
#include "MapleConstants.h"
#include "net/crypto/Crypto.h"
#include "net/packets/PacketProcessor.h"
#include "util/PacketTool.h"

namespace net
{
    TCPConnection::TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets)
        : m_socket(std::move(socket)),
          m_incomingPacketServerQueue(incomingPackets),
          m_ivRecv(k_ivBufferSize),
          m_ivSend(k_ivBufferSize)
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
            Packet packet = PacketProcessor::getHandshake(m_ivRecv, m_ivSend);
            SERVER_INFO("Sending: {}", util::outputPacketHex(packet).str());

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
            m_socket.close();
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
            u16 packetLength = net::getPacketLength(m_tempIncomingPacket.get()->data());

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
            net::decrypt(m_tempIncomingPacket.get()->data(), m_ivRecv.data(), bytesAmount);

            // Add the packet to different processing queues base on packet type (chat packets can go to the server packet queue
            //m_incomingPacketServerQueue.push_back(*m_tempIncomingPacket.get());
            //m_incomingPacketPersonalQueue.push_back(*m_tempIncomingPacket.get());

            SERVER_INFO("Incoming packet hex: {}", util::outputPacketHex(*m_tempIncomingPacket.get()).str());
            SERVER_INFO("Incoming packet dec: {}", util::outputPacketDec(*m_tempIncomingPacket.get()).str());
            SERVER_INFO("Incoming packet string: {}", util::outputPacketString(*m_tempIncomingPacket.get()).str());
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
        bool writingMessage = !m_outgoingPacketQueue.empty();
        m_outgoingPacketQueue.push_back(packet);

        // If we're already writing packets, the packet will be sent eventually anyways
        if (!writingMessage)
            writePacket();
    }

    void TCPConnection::writePacket()
    {
        Packet outgoingPacket = m_outgoingPacketQueue.pop_front();
        size_t packetLength = outgoingPacket.size();

        Packet tempOutgoingPacketBuffer(packetLength + 4);

        // Create packet header
        net::createPacketHeader(tempOutgoingPacketBuffer.data(), m_ivSend.data(), static_cast<u16>(packetLength));

        // Move packet bytes to new buffer
        std::copy(outgoingPacket.begin(), outgoingPacket.end(), tempOutgoingPacketBuffer.begin() + 4);

        // Encrypt packet
        net::encrypt(tempOutgoingPacketBuffer.data(), m_ivSend.data(), static_cast<u16>(packetLength));

        // start an async read operation to receive the header of the next packet
        asio::async_write(m_socket,
                          asio::buffer(tempOutgoingPacketBuffer.data(), packetLength),
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
                SERVER_INFO("No more packets to write.");
                return;
            }
            
            writePacket();
        }
        else
        {
            SERVER_WARN("[{}] Write Packet Fail.", m_socket.remote_endpoint().address().to_string());
            SERVER_WARN(ec.message());
            disconnect();
        }
    }

    const tcp::socket& TCPConnection::getSocket() const
    {
        return m_socket;
    }

    const Packet& TCPConnection::getIvRecv() const
    {
        return m_ivRecv;
    }
    
    const Packet& TCPConnection::getIvSend() const
    {
        return m_ivSend;
    }
}