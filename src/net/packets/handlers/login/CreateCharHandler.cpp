#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleCreateChar(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleCreateChar");

    u16 loginOk = 0;
}