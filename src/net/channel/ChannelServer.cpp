#include "ChannelServer.h"

#include "constants/PacketConstant.h"

namespace net
{
    ChannelServer::ChannelServer(asio::io_context& io_context, uint16_t port) : 
        TCPServerInterface(io_context, port)
    {
        //Register Packet Handlers
        //m_packetHandlers[static_cast<byte>(constant::RecvOps::k_PONG)] = &PacketHandler::handlePong;
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