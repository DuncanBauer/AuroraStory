#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handlePlayerDC(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handlePlayerDC");

    u16 loginOk = 0;
}