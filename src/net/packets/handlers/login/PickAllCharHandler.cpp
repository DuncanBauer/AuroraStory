#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handlePickAllChar(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handlePickAllChar");

    u16 loginOk = 0;
}