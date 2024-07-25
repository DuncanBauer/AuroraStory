#include "TCPConnection.h"
#include "net/crypto/Crypto.h"
#include "MapleConstants.h"

namespace net
{
    TCPConnection::TCPConnection(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets)
        : m_socket(std::move(socket)),
          m_incomingPackets(incomingPackets),
          m_ivRecv(k_ivBufferSize),
          m_ivSend(k_ivBufferSize)
    {}

    TCPConnection::~TCPConnection()
    {
        disconnect();
    }

    // Connect to client
    void TCPConnection::connect(TCPServerInterface* server, uint32_t uid)
    {
        if (m_socket.is_open())
            readHeader();
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

    tcp::socket& TCPConnection::getSocket()
    {
        return m_socket;
    }

    void TCPConnection::readHeader()
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

    void TCPConnection::readHeaderHandler(const std::error_code& ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            // get the packet length from the header buffer
            unsigned short packetLength = net::getPacketLength(m_tempIncomingPacket.get()->data());

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
            disconnect();
        }
    }

    void TCPConnection::readBodyHandler(const std::error_code& ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            // get the packet length
            unsigned short bytes_amount = static_cast<unsigned short>(bytes_transferred);

            // decrypt the packet
            net::decrypt(m_tempIncomingPacket.get()->data(), m_ivRecv.data(), bytes_amount);

            // handle the packet
            m_player->handlePacket(bytes_amount);

            // start an async read operation to receive the header of the next packet
            readHeader();
        }
        else
        {
            disconnect();
        }
    }






























































    void TCPConnection::send(const Packet& packet)
    {
        bool writingMessage = !m_outgoingPackets.empty();
        m_outgoingPackets.push_back(packet);

        if (!writingMessage)
            writeHeader();
    }

    void TCPConnection::writeHeader()
    {
        asio::async_write(m_socket, asio::buffer(&m_outgoingPackets.front(), 4),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    if (m_outgoingPackets.front().size() > 0)
                        writeBody();
                    else
                    {
                        m_outgoingPackets.pop_front();
                        if (!m_outgoingPackets.empty())
                            writeHeader();
                    }
                }
                else
                {
                    SERVER_WARN("[{}] Write Header Fail.", m_socket.remote_endpoint().address().to_string());
                    SERVER_WARN(ec.message());
                    m_socket.close();
                }
            });
    }

    void TCPConnection::writeBody()
    {
        asio::async_write(m_socket, asio::buffer(m_outgoingPackets.front().data(), m_outgoingPackets.front().size()),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    m_outgoingPackets.pop_front();
                    if (!m_outgoingPackets.empty())
                        writeHeader();
                }
                else
                {
                    SERVER_WARN("[{}] Write Body Fail.", m_socket.remote_endpoint().address().to_string());
                    SERVER_WARN(ec.message());
                    m_socket.close();
                }
            });
    }
}