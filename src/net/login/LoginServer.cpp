#include "LoginServer.h"
#include "Master.h"
#include "game/Player.h"

LoginServer::LoginServer(asio::io_context& io_context)
    : TCPServerInterface(io_context, 8484)
{
    //m_loginWorker = std::thread(&LoginServer::updateLoginQueue, this);
}

LoginServer::~LoginServer()
{
}

LoginServer& LoginServer::getInstance()
{
    static LoginServer instance(Master::getInstance().getIoContext()); // Guaranteed to be destroyed
    return instance;
}

void LoginServer::onClientConnect(ClientConnection client)
{

}

void LoginServer::onClientDisconnect(ClientConnection client)
{

}

void LoginServer::onMessage(Packet& packet)
{

}