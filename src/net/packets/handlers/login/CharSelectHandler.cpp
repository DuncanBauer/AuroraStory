#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleCharSelect(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleCharSelect");

    u16 loginOk = 0;
}