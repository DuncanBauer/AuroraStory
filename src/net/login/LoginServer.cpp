#include "LoginServer.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    LoginServer::LoginServer(asio::io_context& io_context, uint16_t port) : 
        TCPServerInterface(io_context, port)
    {
        //Register Packet Handlers
        m_packetHandlers[static_cast<byte>(RecvOps::PONG)] = &PacketHandler::handlePong;
    }

    LoginServer::~LoginServer()
    {}

    void LoginServer::onClientConnect(clientConnection client)
    {
        PacketCreator packetCreator;
        packetCreator.getHandshake(m_ivRecv, m_ivSend);
        std::vector<byte> packet = packetCreator.getPacketBuffer();
        client->send(packet);
    
        packetCreator.outputPacketBuffer();
        packetCreator.clearPacketBuffer();
    }

    void LoginServer::onClientDisconnect(clientConnection client)
    {
    }

    void LoginServer::onMessage(Packet& packet)
    {
    }
}