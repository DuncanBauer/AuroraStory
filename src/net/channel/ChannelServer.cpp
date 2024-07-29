#include <asio.hpp>

#include "ChannelServer.h"

ChannelServer::ChannelServer(asio::io_context& io_context, u16 channelServerPort)
    : TCPServerInterface(io_context, channelServerPort)
{
}

ChannelServer::~ChannelServer()
{
}

void ChannelServer::onClientConnect(ClientConnection client)
{
}

void ChannelServer::onClientDisconnect(ClientConnection client)
{
}

void ChannelServer::onMessage(Packet& packet)
{
}