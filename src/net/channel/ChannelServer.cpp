#include "ChannelServer.h"

namespace net
{
    ChannelServer::ChannelServer(asio::io_context& io_context, uint16_t port) : TCPServerInterface(io_context, port)
    {
        //Register Packet Handlers
        //m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = [](clientConnection& client, Packet& packet) { PacketHandler::handlePong(client, packet); };
        m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = &PacketHandler::handlePong;
    }

    ChannelServer::~ChannelServer()
    {}

    MongoDbHandler& ChannelServer::getDbHandler()
    {
        return m_dbHandler;
    }

    bool ChannelServer::onClientConnect(clientConnection client)
    {
        // Client passed validation, so send them a packet to inform them they can communicate
        Packet packet;
        packet.header.id = static_cast<byte>(RecvOps::AFTER_LOGIN);
        client->send(packet);
        return true;
    }

    void ChannelServer::onClientDisconnect(clientConnection client)
    {
    }

    void ChannelServer::onMessage(Packet& packet)
    {
        m_packetHandlers[packet.header.id](packet);
    }
}