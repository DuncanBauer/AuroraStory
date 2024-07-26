#include "LoginServer.h"
#include "constants/PacketConstant.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context, uint16_t port) : 
        TCPServerInterface(io_context, port)
    {
        //Register Packet Handlers
        m_packetHandlers[static_cast<byte>(constant::RecvOps::k_PONG)] = &PacketHandler::handlePong;
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