#include "TCPServerInterface.h"
#include "game/Player.h"

namespace net
{
    TCPServerInterface::TCPServerInterface(asio::io_context& io_context, uint16_t port) :
        m_ioContext(io_context),
        m_acceptor(m_ioContext, tcp::endpoint(tcp::v4(), port))
    {}

    TCPServerInterface::~TCPServerInterface()
    {
        stop();
    }

    bool TCPServerInterface::start()
    {
        try
        {
            listenForClientConnection();
        }
        catch (std::exception& e)
        {
            SERVER_ERROR("[SERVER] Exception: {}", e.what());
            return false;
        }

        SERVER_INFO("[SERVER] Started!");
        return true;
    }

    void TCPServerInterface::stop()
    {
        SERVER_INFO("[SERVER] Stopped!");
    }

    void TCPServerInterface::listenForClientConnection()
    {
        m_acceptor.async_accept(
            [this](std::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    SERVER_INFO("[SERVER] New Connection: {}:{}", socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port());

                    std::shared_ptr<game::Player> conn = std::make_shared<game::Player>(std::move(socket));

                    onClientConnect(conn);
                    if (conn->isConnected())
                    {
                        m_connections.push_back(std::move(conn));
                        m_connections.back()->connect(this);
                        SERVER_INFO("[{}] Connection Approved", m_connections.back()->getSocket().remote_endpoint().address().to_string());
                    }
                    else
                    {
                        SERVER_INFO("[-----] Connection Denied");
                    }
                }
                else
                {
                    SERVER_INFO("[SERVER] New Connection Error: {}", ec.message().data());
                }

                listenForClientConnection();
            });
    }

    void TCPServerInterface::update(size_t maxPackets, bool wait)
    {
        if (wait)
        {
            size_t packetCount = 0;
            while (packetCount < maxPackets && !m_incomingPackets.empty())
            {
                auto packet = m_incomingPackets.pop_front();
                onMessage(packet);
                packetCount++;
            }
        }
    }

    void TCPServerInterface::messageClient(std::shared_ptr<TCPConnection> client, const Packet& packet)
    {
        if (client && client->isConnected())
            client->send(packet);
        else
        {
            onClientDisconnect(client);
            client.reset();
            m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), client), m_connections.end());
        }
    }

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
}