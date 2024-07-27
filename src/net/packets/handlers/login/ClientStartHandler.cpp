#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleClientStart(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleClientStart");

    u16 loginOk = 0;
}