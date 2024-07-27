#include "util/LoggingTool.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

void PacketHandler::handleRegisterPin(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleRegisterPin");

    u16 loginOk = 0;
}