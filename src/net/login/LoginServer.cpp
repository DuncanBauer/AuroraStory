#include "LoginServer.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context, uint16_t port) : TCPServerInterface(io_context, port)
    {
        //Register Packet Handlers
        m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = &PacketHandler::handlePong;
    }

    LoginServer::~LoginServer()
    {}

    MongoDbHandler& LoginServer::getDbHandler()
    {
        return m_dbHandler;
    }

    bool LoginServer::onClientConnect(clientConnection client)
    {
        //net::
        //write<short>(kPacketHandshakeServerLength + static_cast<short>(kGameMinorVersion.length()));
        //write<short>(kGameVersion);
        //write<std::string>(kGameMinorVersion);
        //write<int>(*(int*)iv_recv);
        //write<int>(*(int*)iv_send);
        //write<signed char>(kGameLocale);


        //// Client passed validation, so send them a packet to inform them they can communicate
        //Packet packet;
        //packet.header.id = static_cast<byte>(RecvOps::AFTER_LOGIN);
        //client->send(packet);
        return true;
    }

    void LoginServer::onClientDisconnect(clientConnection client)
    {
    }

    void LoginServer::onMessage(Packet& packet)
    {
        //m_packetHandlers[packet.header.id](packet);
    }
}