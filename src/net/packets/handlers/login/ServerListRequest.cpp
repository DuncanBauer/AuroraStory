#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleServerListRequest(std::shared_ptr<Player> player, Packet& packet)
{
    for(u16 i = 0; i < Master::getInstance().getWorlds().size(); i++) 
    {
        player->send(PacketCreator::getServerData(
            i, 
            Master::getInstance().getSettings().serverName,
            Master::getInstance().getWorlds()[i]->getChannelLoads())
        );
    }

    player->send(PacketCreator::getEndOfServerList());
}