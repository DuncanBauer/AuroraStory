#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleAfterLogin(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleAfterLogin");

    u16 loginOk = 0;
}