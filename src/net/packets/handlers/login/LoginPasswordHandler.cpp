#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"
#include "game/Player.h"

enum LoginStatus
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
    BANNED
};

void PacketHandler::handleLoginPassword(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleLoginPassword");

    std::string username = PacketProcessor::readMapleString(packet);
    std::string password = PacketProcessor::readMapleString(packet);

    SERVER_INFO("Username: {}", username);
    SERVER_INFO("Password: {}", password);

    player.login(username, password);
    u16 loginOk = 0;

    // if username exists
        // check ban status
        // check password hash
    // else
        // if auto register enabled
            // register
}
