#include "TCPConnection.h"


namespace net
{
    TCPConnection::TCPConnection(Owner parent, asio::io_context& ioContext, tcp::socket socket, util::ThreadSafeQueue<OwnedPacket>& incomingPackets)
        : m_owner(parent), m_ioContext(ioContext), m_socket(std::move(socket)), m_incomingPackets(incomingPackets)
    {}

    TCPConnection::~TCPConnection()
    {
        disconnect();
    }

    uint32_t TCPConnection::getID() const
    {
        return m_id;
    }

    // Connect to client
    void TCPConnection::connectToClient(TCPServerInterface* server, uint32_t uid)
    {
        if (m_owner == Owner::Server)
        {
            if (m_socket.is_open())
            {
                m_id = uid;
                readHeader();

                // A client has attempted to connect to the server
                // But we want to validate the client first
                // So first send out handshake data
                //writeValidation();

                // Next, wait asynchronously for validation data to be returned from the client
                //readValidation(server);
            }
        }
    }

    // Connect to server
    void TCPConnection::connectToServer(const tcp::resolver::results_type& endpoints)
    {
        if (m_owner == Owner::Client)
        {
            // Request asio attempts to connect to an endpoint
            asio::async_connect(m_socket, endpoints,
                [this](std::error_code ec, tcp::endpoint endpoints)
                {
                    if (!ec)
                    // On connection, server will send packet to validate client
                    //readValidation();
                        readHeader();
                });
        }
    }

    // Disconnect from the client/server
    void TCPConnection::disconnect()
    {
        // If the socket is connected, close it
        if (isConnected())
            asio::post(m_ioContext, [this]() { m_socket.close(); });
    }

    // Check if the connection is still up
    bool TCPConnection::isConnected()
    {
        return m_socket.is_open();
    }

    // Send a written packet to the client/server
    void TCPConnection::send(const Packet& packet)
    {
        asio::post(m_ioContext,
            [this, packet]()
            {
                // If the queue has a message in it, then assume that it is in the process of asynchronously being written.
                bool writingMessage = !m_outgoingPackets.empty();

        // Either way add the message to the queue to be output.
        m_outgoingPackets.push_back(packet);

        // If no messages were available to be written, then start the process of writing the
        // message at the front of the queue.
        if (!writingMessage)
            writeHeader();
            });
    }

    // Read an incoming packet header
    void TCPConnection::readHeader()
    {
        // If this function is called, we are expecting to receive a packet header
        // We know the headers are a fixed size so allocate to that size
        asio::async_read(m_socket, asio::buffer(&m_tempIncomingPacket.header, sizeof(PacketHeader)),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // If there's no error
                    // We've received a complete packet header, check if it has a body after it
                    if (m_tempIncomingPacket.header.size > 0)
                    {
                        // It has a body so allocate space in the packets body vector and read the body
                        m_tempIncomingPacket.body.resize(m_tempIncomingPacket.header.size);
                        readBody();
                    }
                    else
                    {
                        // There's no body with the packet, so add it to the incomingPacket queue
                        addToIncomingPacketQueue();
                    }
                }
                else
                {
                    // Reading from the client went wrong. Close the socket and let the system tidy it up later.
                    spdlog::warn("[{}] Read Header Fail.", m_id);
                    spdlog::warn(ec.message());
                    m_socket.close();
                }
            });
    }

    // Read an incoming packet body
    void TCPConnection::readBody()
    {
        // If this function is called, we are expecting to receive a packet body so wait for the data to arrive
        asio::async_read(m_socket, asio::buffer(m_tempIncomingPacket.body.data(), m_tempIncomingPacket.body.size()),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // No error, the packet is now complete, so add the whole packet to incoming queue
                    addToIncomingPacketQueue();
                }
                else
                {
                    // Reading from the client went wrong. Close the socket and let the system tidy it up later.
                    spdlog::warn("[{}] Read Body Fail.", m_id);
                    spdlog::warn(ec.message());
                    m_socket.close();
                }
            });
    }

    // Adds incoming packets to the packet queue for processing
    void TCPConnection::addToIncomingPacketQueue()
    {
        // Convert to an OwnedPacket and add it to the queue
        if (m_owner == Owner::Server)
            m_incomingPackets.push_back({ this->shared_from_this(), m_tempIncomingPacket });
        else
            m_incomingPackets.push_back({ nullptr, m_tempIncomingPacket });

        // Ready asio to read next packet header
        readHeader();
    }

    // Write a packet header
    void TCPConnection::writeHeader()
    {
        // If this function is called, then there is at least one packet in the outgoing packet queue
        // Allocate a buffer to hold the packet and construct the header
        asio::async_write(m_socket, asio::buffer(&m_outgoingPackets.front().header, sizeof(PacketHeader)),
            [this](std::error_code ec, std::size_t length)
            {
                // asio has send the packet
                // Check for error
                if (!ec)
                {
                    // No error, check if sent packet header has a body
                    if (m_outgoingPackets.front().body.size() > 0)
                    {
                        // If it does, write the body data
                        writeBody();
                    }
                    else
                    {
                        // If there's no body, remove it from the packet queue
                        m_outgoingPackets.pop_front();

                        // If the queue is not empty, send the next header
                        if (!m_outgoingPackets.empty())
                        {
                            writeHeader();
                        }
                    }
                }
                else
                {
                    // There's an error, so output to console and close the socket
                    spdlog::warn("[{}] Write Header Fail.", m_id);
                    spdlog::warn(ec.message());
                    m_socket.close();
                }
            });
    }

    // Write a packet body
    void TCPConnection::writeBody()
    {
        // If this function is called, a header was just sent and had a body, so send its associated body
        asio::async_write(m_socket, asio::buffer(m_outgoingPackets.front().body.data(), m_outgoingPackets.front().body.size()),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // There's no error sending the body
                    // Remove it from the queue
                    m_outgoingPackets.pop_front();

                    // If there's more packets in the queue, send them
                    if (!m_outgoingPackets.empty())
                        writeHeader();
                }
                else
                {
                    // There's an error, so output to console and close the socket
                    spdlog::warn("[{}] Write Body Fail.", m_id);
                    spdlog::warn(ec.message());
                    m_socket.close();
                }
            });
    }
}