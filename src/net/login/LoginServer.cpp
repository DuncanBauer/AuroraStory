#include "LoginServer.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context, u16 port) : 
        TCPServerInterface(io_context, port)
    {
    }

    LoginServer::~LoginServer()
    {}

    void LoginServer::onClientConnect(ClientConnection client)
    {
    }

    void LoginServer::onClientDisconnect(ClientConnection client)
    {
    }

    void LoginServer::onMessage(Packet& packet)
    {
    }
}