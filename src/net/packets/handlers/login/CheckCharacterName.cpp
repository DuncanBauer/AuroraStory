#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/MapleTool.h"
#include "util/PacketTool.h"

void PacketHandler::handleCheckCharacterName(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleCheckCharacterName");
    std::string name = util::PacketTool::readMapleString(packet);
    player->send(PacketCreator::characterNameResponse(name, !util::MapleTool::canCreateCharacter(name, player->getWorld())));
}