#pragma once

#include "TCPConnection.h"
#include "db/MongoDbHandler.h"

namespace net
{
    using asio::ip::tcp;

    typedef void(*fnPointer)(Packet&); // function pointer type
    typedef std::unordered_map<byte, fnPointer> PacketHandlers;

    class TCPServerInterface
    {
    public:
        TCPServerInterface(asio::io_context& io_context, uint16_t port);
        virtual ~TCPServerInterface();

        bool start();
        void stop();
        void listenForClientConnection();
        void update(size_t maxPackets = -1, bool wait = false);

        void messageClient(std::shared_ptr<TCPConnection> client, const Packet& packet);
        void messageAllClients(const Packet& packet, std::shared_ptr<TCPConnection> pIgnoreClient = nullptr);

    protected:
        virtual void onClientConnect(std::shared_ptr<TCPConnection> client) = 0;
        virtual void onClientDisconnect(std::shared_ptr<TCPConnection> client) = 0;
        virtual void onMessage(Packet& packet) = 0;

    protected:
        PacketHandlers m_packetHandlers;
        MongoDbHandler m_dbHandler;

    private:
        asio::io_context& m_ioContext;
        tcp::acceptor m_acceptor;
        util::ThreadSafeQueue<Packet> m_incomingPackets;
        std::deque<std::shared_ptr<TCPConnection>> m_connections;
    };
}