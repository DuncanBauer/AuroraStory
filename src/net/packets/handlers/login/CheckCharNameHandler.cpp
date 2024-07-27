#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleCheckCharName(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleCheckCharName");

    u16 loginOk = 0;
}