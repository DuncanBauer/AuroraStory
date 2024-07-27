#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketProcessor.h"

void PacketHandler::handleRegisterPin(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleRegisterPin");

    u16 loginOk = 0;
}