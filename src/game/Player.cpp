#include "pch.h"

#include "Player.h"

#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

namespace game
{
    Player::Player(tcp::socket socket, util::ThreadSafeQueue<net::Packet>& incomingPackets) 
        : TCPConnection(std::move(socket), incomingPackets)
    {
    }
    
    Player::~Player()
    {}

    void Player::processPacket(net::Packet& packet)
    {
        // Remove game version / packet size
        uint16_t packetHeader = net::PacketCreator::readShort(packet);
        std::cout << util::outputShortHex(packetHeader).str() << '\n';

        // Get opCode
        uint16_t opCode = net::PacketCreator::readShort(packet);
        std::cout << util::outputShortHex(opCode).str() << '\n';
        if (!net::PacketHandler::m_packetHandlers[opCode])
        {
            SERVER_ERROR("No handler for this opCode");
            return;
        }

        net::PacketHandler::m_packetHandlers[opCode](packet);
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
}