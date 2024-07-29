#pragma once

#include "TCPConnection.h"

namespace net
{
    using asio::ip::tcp;

    class TCPServerInterface
    {
    public:
        TCPServerInterface(asio::io_context& io_context, u16 port);
        virtual ~TCPServerInterface();

        bool start();
        void stop();
        void listenForClientConnection();
        void update(size_t maxPackets = -1, bool wait = false);

        void messageClient(ClientConnection client, const Packet& packet);
        void messageAllClients(const Packet& packet, ClientConnection pIgnoreClient = nullptr);

    protected:
        virtual void onClientConnect(ClientConnection client) = 0;
        virtual void onClientDisconnect(ClientConnection client) = 0;
        virtual void onMessage(Packet& packet) = 0;

    private:
        asio::io_context& m_ioContext;
        tcp::acceptor m_acceptor;
        util::ThreadSafeQueue<Packet> m_incomingPackets;
        std::deque<ClientConnection> m_connections;
    };
}