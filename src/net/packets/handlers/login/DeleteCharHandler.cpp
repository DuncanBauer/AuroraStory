#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleDeleteChar(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleDeleteChar");

    u16 loginOk = 0;
}