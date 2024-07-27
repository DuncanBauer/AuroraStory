#include "Player.h"

#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

Player::Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets) 
    : TCPConnection(std::move(socket), incomingPackets)
{}
    
Player::~Player()
{}

void Player::processPacket(Packet& packet)
{
    //// Remove game version / packet size
    //u16 packetHeader = PacketProcessor::readShort(packet);
    //SERVER_INFO("Player::processPacket - Packet Header: {}", util::outputShortHex(packetHeader).str());

    //// Get opCode
    //u16 opCode = PacketProcessor::readShort(packet);
    //SERVER_INFO("Player::processPacket - OpCode: {}", util::outputShortHex(opCode).str());

    u16 opCode = util::PacketTool::readShort(packet);
    if (!PacketHandler::m_packetHandlers[opCode])
    {
        SERVER_ERROR("No handler for this opCode");
        return;
    }

    PacketHandler::m_packetHandlers[opCode](*this, packet);
}

int Player::login(const std::string& username, const std::string& password)
{

    return 0;
}

int Player::logout()
{
    return 0;
}

int Player::changeChannel()
{
    return 0;
}