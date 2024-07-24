#include "TCPServer.h"

namespace net
{
    TCPServer::TCPServer(uint16_t port) : TCPServerInterface(port)
    {
        //Register Packet Handlers
        //m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = [](clientConnection& client, Packet& packet) { PacketHandler::handlePong(client, packet); };
        m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = &PacketHandler::handlePong;
    }

    TCPServer::~TCPServer()
    {}

    MongoDbHandler& TCPServer::getDbHandler()
    {
        return m_dbHandler;
    }

    bool TCPServer::onClientConnect(clientConnection client)
    {
        // Client passed validation, so send them a packet to inform them they can communicate
        Packet packet;
        packet.header.id = static_cast<byte>(RecvOps::AFTER_LOGIN);
        client->send(packet);
        return true;
    }

    void TCPServer::onClientDisconnect(clientConnection client)
    {
    }

    void TCPServer::onMessage(clientConnection client, Packet& packet)
    {
        m_packetHandlers[packet.header.id](client, packet);
    }
}