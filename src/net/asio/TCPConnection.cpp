#include "TCPConnection.h"
#include "constants/MapleConstants.h"
#include "net/crypto/Crypto.h"
#include "net/packets/PacketCreator.h"
#include "util/PacketTool.h"

namespace net
{
    TCPConnection::TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets)
        : m_socket(std::move(socket)),
          m_incomingPackets(incomingPackets),
          m_ivRecv(constant::k_ivBufferSize),
          m_ivSend(constant::k_ivBufferSize)
    {}

    TCPConnection::~TCPConnection()
    {
        disconnect();
    }

    // Connect to client
    void TCPConnection::connect(TCPServerInterface* server, uint32_t uid)
    {
        if (m_socket.is_open())
        {
            PacketCreator packetCreator;
            std::vector<byte> packet = packetCreator.getHandshake(m_ivRecv, m_ivSend);
            std::cout << "Sending: " << util::outputPacketHex(packet).str();

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
        std::cout << "Start Read Packet\n";
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
        std::cout << "Start Read Header: ";
        std::cout << util::outputPacketHex(*m_tempIncomingPacket.get()).str() << '\n';

        if (!ec)
        {
            // get the packet length from the header buffer
            unsigned short packetLength = net::getPacketLength(m_tempIncomingPacket.get()->data());
            std::cout << "Received packet length: " << packetLength << '\n';

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
        std::cout << "Start Read Body: ";
        if (!ec)
        {
            // get the packet length
            unsigned short bytesAmount = static_cast<unsigned short>(bytesTransferred);

            // decrypt the packet
            net::decrypt(m_tempIncomingPacket.get()->data(), m_ivRecv.data(), bytesAmount);
            m_incomingPackets.push_back(*m_tempIncomingPacket.get());

            std::cout << util::outputPacketHex(*m_tempIncomingPacket.get()).str() << '\n';
            std::cout << util::outputPacketString(*m_tempIncomingPacket.get()).str() << '\n';

            // handle the packet
            handlePacket(bytesAmount);

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
        bool writingMessage = !m_outgoingPackets.empty();
        m_outgoingPackets.push_back(packet);

        // If we're already writing packets, the packet will be sent eventually anyways
        if (!writingMessage)
            writePacket();
    }

    void TCPConnection::writePacket()
    {
        std::vector<byte> outgoingPacket = m_outgoingPackets.pop_front();
        size_t packetLength = outgoingPacket.size();

        std::vector<byte> tempOutgoingPacketBuffer(packetLength + 4);

        // Create packet header
        net::createPacketHeader(tempOutgoingPacketBuffer.data(), m_ivSend.data(), static_cast<unsigned short>(packetLength));

        // Move packet bytes to new buffer
        std::copy(outgoingPacket.begin(), outgoingPacket.end(), tempOutgoingPacketBuffer.begin() + 4);

        // Encrypt packet
        net::encrypt(tempOutgoingPacketBuffer.data(), m_ivSend.data(), static_cast<unsigned short>(packetLength));

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
            if (m_outgoingPackets.empty())
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

    void TCPConnection::handlePacket(int bytesAmount)
    {}

    const tcp::socket& TCPConnection::getSocket() const
    {
        return m_socket;
    }

    const std::vector<byte>& TCPConnection::getIvRecv() const
    {
        return m_ivRecv;
    }
    
    const std::vector<byte>& TCPConnection::getIvSend() const
    {
        return m_ivSend;
    }
}