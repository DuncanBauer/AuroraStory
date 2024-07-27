#pragma once

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

namespace net
{
    class ChannelServer : public TCPServerInterface
    {
    public:
        ChannelServer(asio::io_context& io_context, u16 port);
        ~ChannelServer();

    protected:
        void onClientConnect(ClientConnection client) override;
        void onClientDisconnect(ClientConnection client) override;
        void onMessage(Packet& packet) override;
    };
}