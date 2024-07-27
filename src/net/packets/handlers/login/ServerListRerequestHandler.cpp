#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleServerListRerequest(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleServerListRerequest");

    u16 loginOk = 0;
}