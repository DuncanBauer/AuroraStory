#include "Player.h"

namespace game
{
    Player::Player(tcp::socket socket) : TCPConnection(std::move(socket))
    {
    }
    
    Player::~Player()
    {}

    Player::handlePacket()
    {

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