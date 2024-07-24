#pragma once

#include "db/MongoDbHandler.h"
#include "net/packets/RecvOps.h"
#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

namespace net
{
    class ChannelServer : public TCPServerInterface
    {
        typedef void(*fnPointer)(Packet&); // function pointer type
        typedef std::unordered_map<byte, fnPointer> PacketHandlers;

    public:
        ChannelServer(asio::io_context& io_context, uint16_t port);

        ~ChannelServer();

        MongoDbHandler& getDbHandler();

    protected:
        bool onClientConnect(clientConnection client) override;

        void onClientDisconnect(clientConnection client) override;

        void onMessage(Packet& packet) override;

    private:
        PacketHandlers m_packetHandlers;
        MongoDbHandler m_dbHandler;
    };
}