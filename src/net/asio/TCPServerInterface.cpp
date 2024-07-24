#include "TCPServerInterface.h"

namespace net
{
    TCPServerInterface::TCPServerInterface(asio::io_context& io_context, uint16_t port) : m_ioContext(io_context), m_acceptor(m_ioContext, tcp::endpoint(tcp::v4(), port))
    {}

    TCPServerInterface::~TCPServerInterface()
    {
        stop();
    }

    // Starts the server
    bool TCPServerInterface::start()
    {
        try
        {
            listenForClientConnection();
        }
        catch (std::exception& e)
        {
            // Something prohibited the server from listening
            SERVER_ERROR("[SERVER] Exception: {}", e.what());
            return false;
        }

        SERVER_INFO("[SERVER] Started!");
        return true;
    }

    // Stops the server
    void TCPServerInterface::stop()
    {
        // Output to console
        SERVER_INFO("[SERVER] Stopped!");
    }

    // Instructs asio to wait for a client so it doesn't simply stop
    void TCPServerInterface::listenForClientConnection()
    {
        // Have asio context wait for client connections
        m_acceptor.async_accept(
            [this](std::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    // No errors receiving incoming connection
                    SERVER_INFO("[SERVER] New Connection: {}:{}", socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port());

                    // Create new connection to handle client
                    std::shared_ptr <TCPConnection> conn = std::make_shared<TCPConnection>(
                        m_ioContext,
                        std::move(socket),
                        m_incomingPackets);

                    // Give the user a chance to deny connection
                    if (onClientConnect(conn))
                    {
                        // Add connection to connections container
                        m_connections.push_back(std::move(conn));

                        // Inform connection to wait for incoming packets
                        m_connections.back()->connectToClient(this, m_idCounter++);

                        SERVER_INFO("[{}] Connection Approved", m_connections.back()->getID());
                    }
                    else
                    {
                        // Connection will go out of scope without tasks and will get destroyed by the smart pointer    
                        SERVER_INFO("[-----] Connection Denied");
                    }
                }
                else
                {
                    // Error has occurred while accepting client
                    SERVER_INFO("[SERVER] New Connection Error: {}", ec.message().data());
                }

                // Wait for more connections
                listenForClientConnection();
            });
    }

    // Send a message to a unique client
    void TCPServerInterface::messageClient(std::shared_ptr<TCPConnection> client, const Packet& packet)
    {
        // Check if client is legit
        if (client && client->isConnected())
        {
            // Send the packet
            client->send(packet);
        }
        else
        {
            // Remove the client since we can't communicate with it
            // Handle any disconnect requirements of the server
            onClientDisconnect(client);

            // Reset the shared pointer to nullptr
            client.reset();

            // Remove the connection from the connections container
            m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), client), m_connections.end());
        }
    }

    // Send a message to all clients
    void TCPServerInterface::messageAllClients(const Packet& packet, std::shared_ptr<TCPConnection> pIgnoreClient)
    {
        // Flag for an invalid client
        bool bInvalidClientExists = false;

        // Iterate through all clients in container
        for (auto& client : m_connections)
        {
            // Check client is connected...
            if (client && client->isConnected())
            {
                // ..it is!
                if (client != pIgnoreClient)
                    client->send(packet);
            }
            else
            {
                // The client couldnt be contacted, so assume it has disconnected.
                onClientDisconnect(client);

                // Reset the shared pointer to nullptr
                client.reset();

                // Set this flag to then remove dead clients from container
                bInvalidClientExists = true;
            }
        }

        // Remove dead clients, all in one go - this way, we dont invalidate the
        // container as we iterated through it.
        if (bInvalidClientExists)
            m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), nullptr), m_connections.end());
    }

    // Forces to the server to process incoming messages
    void TCPServerInterface::update(size_t maxPackets, bool wait)
    {
        if (wait)
        {
            // Process messages up to maxPackets
            size_t packetCount = 0;
            while (packetCount < maxPackets && !m_incomingPackets.empty())
            {
                // Grab first packet
                auto packet = m_incomingPackets.pop_front();

                // Handle packet
                onMessage(packet);

                packetCount++;
            }
        }
    }

    // Called when a client connects
    bool TCPServerInterface::onClientConnect(std::shared_ptr<TCPConnection> client)
    {
        return false;
    }

    // Called when a client disconnects
    void TCPServerInterface::onClientDisconnect(std::shared_ptr<TCPConnection> client)
    {}

    // Called when a message is received
    void TCPServerInterface::onMessage(Packet& packet)
    {}
}