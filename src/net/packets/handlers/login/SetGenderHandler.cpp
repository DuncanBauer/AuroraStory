#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleSetGender(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleSetGender");

    u16 loginOk = 0;
}