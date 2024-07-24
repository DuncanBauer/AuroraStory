#pragma once

#include "db/MongoDbHandler.h"
#include "RecvOps.h"
#include "PacketHandler.h"
#include "TCPServerInterface.h"

namespace net
{
    class TCPServer : public TCPServerInterface
    {
        typedef void(*fnPointer)(clientConnection, Packet&); // function pointer type
        typedef std::unordered_map<byte, fnPointer> PacketHandlers;

    public:
        TCPServer(uint16_t port);

        ~TCPServer();

        MongoDbHandler& getDbHandler();

    protected:
        bool onClientConnect(clientConnection client) override;

        void onClientDisconnect(clientConnection client) override;

        void onMessage(clientConnection client, Packet& packet) override;

    private:
        PacketHandlers m_packetHandlers;
        MongoDbHandler m_dbHandler;
    };
}