#pragma once

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

class ChannelServer : public net::TCPServerInterface
{
public:
    ChannelServer(asio::io_context& io_context, u16 channelServerPort);
    ~ChannelServer();

protected:
    void onClientConnect(ClientConnection client) override;
    void onClientDisconnect(ClientConnection client) override;
    void onMessage(Packet& packet) override;

private:
};