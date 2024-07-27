#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleServerStatusRequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleServerStatusRequest");

    u16 loginOk = 0;
}