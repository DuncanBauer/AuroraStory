#include "Player.h"

namespace game
{
    Player::Player(tcp::socket socket, util::ThreadSafeQueue<net::Packet>& incomingPackets) 
        : TCPConnection(std::move(socket), incomingPackets)
    {
    }
    
    Player::~Player()
    {}

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