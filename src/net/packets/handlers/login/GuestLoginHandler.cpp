#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

enum LoginStatus
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
    BANNED
};

void PacketHandler::handleGuestLogin(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleGuestLogin");

    u16 loginOk = 0;
}