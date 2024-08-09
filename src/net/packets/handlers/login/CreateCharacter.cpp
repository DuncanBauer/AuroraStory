#include <unordered_set>

#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleCreateCharacter(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleCreateCharacter");

    std::string name = util::PacketTool::readMapleString(packet);
    //u32 job          = util::PacketTool::readInt(packet); // Not available til v75? Only adventurer classes in v62
    u32 face         = util::PacketTool::readInt(packet);
    u32 hair         = util::PacketTool::readInt(packet);
    u32 hairColor    = util::PacketTool::readInt(packet);
    u32 skinColor    = util::PacketTool::readInt(packet);
    u32 top          = util::PacketTool::readInt(packet);
    u32 bottom       = util::PacketTool::readInt(packet);
    u32 shoes        = util::PacketTool::readInt(packet);
    u32 weapon       = util::PacketTool::readInt(packet);
    u32 gender       = util::PacketTool::readByte(packet);
    u32 baseStr      = util::PacketTool::readByte(packet);
    u32 baseDex      = util::PacketTool::readByte(packet);
    u32 baseInt      = util::PacketTool::readByte(packet);
    u32 baseLuk      = util::PacketTool::readByte(packet);

	//// KoC and Aran arent available in v62
    //if (job == 0) 
    //{ // Knights of Cygnus
    //    status = NoblesseCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
    //}
    //else if (job == 1)
    //{ // Adventurer
    //    status = BeginnerCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
    //}
    //else if (job == 2)
    //{ // Aran
    //    status = LegendCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
    //}
    //else 
    //{
    //    c.announce(PacketCreator::deleteCharacterResponse(0, 9));
    //    return;
    //}
    
    u32 status = Character::createCharacter(player, name, face, hair, hairColor, skinColor,
                                            top, bottom, shoes, weapon,
                                            gender, baseStr, baseDex, baseInt, baseLuk);
    if (status == -2) 
    {
        player->send(PacketCreator::characterCreationFailed(0, 9));
    }
}