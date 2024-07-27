#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleCharListRequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleCharListRequest");

    u16 loginOk = 0;
}