#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleViewAllChar(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleViewAllChar");

    u16 loginOk = 0;
}