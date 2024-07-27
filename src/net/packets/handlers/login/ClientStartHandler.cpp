#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleClientStart(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleClientStart");

    u16 loginOk = 0;
}