#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleRelog(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleRelog");

    u16 loginOk = 0;
}