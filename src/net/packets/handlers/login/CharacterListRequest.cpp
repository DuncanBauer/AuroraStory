#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleCharacterListRequest(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleCharListRequest");
    
    int server = util::PacketTool::readByte(packet);
    int channel = util::PacketTool::readByte(packet) + 1;
    player->setWorld(server);
    player->setChannel(channel);
    player->send(PacketCreator::getCharacterList(player, server));
}