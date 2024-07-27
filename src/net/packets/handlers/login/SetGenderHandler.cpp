#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleSetGender(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleSetGender");

    u16 loginOk = 0;
}