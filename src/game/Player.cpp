#include "Player.h"

#include "net/packets/PacketHandler.h"
#include "constants/PacketConstant.h"

namespace game
{
    Player::Player(tcp::socket socket, util::ThreadSafeQueue<net::Packet>& incomingPackets) 
        : TCPConnection(std::move(socket), incomingPackets)
    {
    }
    
    Player::~Player()
    {}

    void Player::processPackets()
    {
        m_processingPackets = true;
        size_t packetCount = 0;
        while (packetCount < constant::maxPackets && !m_incomingPacketPersonalQueue.empty())
        {
            net::Packet packet = m_incomingPacketPersonalQueue.pop_front();
            net::PacketHandler::m_packetHandlers[packet.front()](packet);
            packetCount++;
        }
        m_processingPackets = false;
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