#pragma once

#include "TCPConnection.h"

namespace net
{
    using asio::ip::tcp;

    class TCPServerInterface
    {
    public:
        TCPServerInterface(asio::io_context& io_context, uint16_t port);

        virtual ~TCPServerInterface();

        // Starts the server
        bool start();

        // Stops the server
        void stop();

        // Instructs asio to wait for a client so it doesn't simply stop
        void listenForClientConnection();

        // Send a message to a unique client
        void messageClient(std::shared_ptr<TCPConnection> client, const Packet& packet);

        // Send a message to all clients
        void messageAllClients(const Packet& packet, std::shared_ptr<TCPConnection> pIgnoreClient = nullptr);

        // Forces to the server to process incoming messages
        void update(size_t maxPackets = -1, bool wait = false);

    protected:
        // These should be overridden in a derived class
        // Called when a client connects
        virtual bool onClientConnect(std::shared_ptr<TCPConnection> client);

        // Called when a client disconnects
        virtual void onClientDisconnect(std::shared_ptr<TCPConnection> client);

        // Called when a message is received
        virtual void onMessage(Packet& packet);

    private:
        // Order of declaration matters regardless of whether i want it to be
        asio::io_context& m_ioContext;

        // Handles incoming connection attemps
        tcp::acceptor m_acceptor;

        // ThreadSafeQueue for incoming packets
        util::ThreadSafeQueue<Packet> m_incomingPackets;

        // Queue for connections
        std::deque<std::shared_ptr<TCPConnection>> m_connections;

        // Clients will be identified by id
        uint32_t m_idCounter = 10000;
    };
}