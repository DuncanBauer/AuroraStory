#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleServerListRequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleServerListRequest");

    u16 loginOk = 0;
}