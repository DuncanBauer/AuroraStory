#include "ChannelServer.h"

#include "constants/PacketConstant.h"

namespace net
{
    ChannelServer::ChannelServer(asio::io_context& io_context, uint16_t port) : 
        TCPServerInterface(io_context, port)
    {
    }

    ChannelServer::~ChannelServer()
    {}

    void ChannelServer::onClientConnect(clientConnection client)
    {
    }

    void ChannelServer::onClientDisconnect(clientConnection client)
    {
    }

    void ChannelServer::onMessage(Packet& packet)
    {
    }
}