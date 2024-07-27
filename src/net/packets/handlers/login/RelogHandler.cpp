#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleRelog(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleRelog");

    u16 loginOk = 0;
}