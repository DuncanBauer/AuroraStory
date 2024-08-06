#pragma once

#include "net/packets/PacketHandler.h"
#include "net/asio/TCPServerInterface.h"

class ChannelServer : public net::TCPServerInterface
{
public:
    ChannelServer() = delete;
    ChannelServer(asio::io_context& io_context, u16 channelServerPort);
    ~ChannelServer();

    inline u16 getUserLoad() { return m_userLoad; }

protected:
    void onClientConnect(ClientConnection client)    override;
    void onClientDisconnect(ClientConnection client) override;
    void onMessage(Packet& packet)                   override;

private:
    u16 m_port     = 0;
    u16 m_userLoad = 0;
};