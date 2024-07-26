#include "pch.h"

#include "LoginServer.h"
#include "constants/PacketConstant.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context, uint16_t port) : 
        TCPServerInterface(io_context, port)
    {
    }

    LoginServer::~LoginServer()
    {}

    void LoginServer::onClientConnect(clientConnection client)
    {
    }

    void LoginServer::onClientDisconnect(clientConnection client)
    {
    }

    void LoginServer::onMessage(Packet& packet)
    {
    }
}