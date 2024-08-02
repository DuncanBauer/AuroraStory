#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleServerStatusRequest(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleServerStatusRequest");
    player->send(PacketCreator::getServerStatus(0));
}