#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/LoggingTool.h"
#include "util/PacketTool.h"

void PacketHandler::handleServerStatusRequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleServerStatusRequest");

    u16 loginOk = 0;
}