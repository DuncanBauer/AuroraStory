#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handlePong(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handlePong");

    u16 loginOk = 0;
}
