#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handlePlayerDC(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handlePlayerDC");

    u16 loginOk = 0;
}