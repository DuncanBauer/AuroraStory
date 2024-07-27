#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handlePong(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handlePong");

    u16 loginOk = 0;
}
