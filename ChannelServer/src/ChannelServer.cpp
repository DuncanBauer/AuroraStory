#include <asio.hpp>

#include "ChannelServer.h"

namespace net
{
    ChannelServer::ChannelServer(asio::io_context& io_context, u16 port) 
        : TCPServerInterface(io_context, port)
    {
    }

    ChannelServer::~ChannelServer()
    {}

    void ChannelServer::onClientConnect(ClientConnection client)
    {
    }

    void ChannelServer::onClientDisconnect(ClientConnection client)
    {
    }

    void ChannelServer::onMessage(Packet& packet)
    {
    }
}