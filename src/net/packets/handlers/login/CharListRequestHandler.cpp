#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleCharListRequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleCharListRequest");

    u16 loginOk = 0;
}