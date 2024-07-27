#pragma once

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

namespace net
{
    class LoginServer : public TCPServerInterface
    {
    public:
        LoginServer(asio::io_context& io_context, u16 port);
        ~LoginServer();

    protected:
        void onClientConnect(ClientConnection client) override;
        void onClientDisconnect(ClientConnection client) override;
        void onMessage(Packet& packet) override;
    };
}