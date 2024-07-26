#pragma once

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

namespace net
{
    class LoginServer : public TCPServerInterface
    {
    public:
        LoginServer(asio::io_context& io_context, uint16_t port);
        ~LoginServer();

    protected:
        void onClientConnect(clientConnection client) override;
        void onClientDisconnect(clientConnection client) override;
        void onMessage(Packet& packet) override;
    };
}