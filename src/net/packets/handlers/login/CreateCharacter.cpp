#include <unordered_set>

#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleCreateCharacter(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleCreateCharacter");

	//// Starting equip options
	//std::unordered_set<u32> IDs = {
	//	1302000, 1312004, 1322005, 1442079,// weapons
	//	1040002, 1040006, 1040010, 1041002, 1041006, 1041010, 1041011, 1042167,// bottom
	//	1060002, 1060006, 1061002, 1061008, 1062115, // top
	//	1072001, 1072005, 1072037, 1072038, 1072383,// shoes
	//	30000, 30010,30020, 30030, 31000, 31040, 31050,// hair  
	//	20000, 20001, 20002, 21000, 21001, 21002, 21201, 20401, 20402, 21700, 20100  //face
	//	//#NeverTrustStevenCode
	//};

	//std::string name = util::PacketTool::readMapleString(packet);
	//u32 job = util::PacketTool::readInt(packet);
	//u32 face = util::PacketTool::readInt(packet);

	//u32 hair = util::PacketTool::readInt(packet);
	//u32 haircolor = util::PacketTool::readInt(packet);
	//u32 skincolor = util::PacketTool::readInt(packet);

	//u32 top = util::PacketTool::readInt(packet);
	//u32 bottom = util::PacketTool::readInt(packet);
	//u32 shoes = util::PacketTool::readInt(packet);
	//u32 weapon = util::PacketTool::readInt(packet);
	//u32 gender = util::PacketTool::readByte(packet);

	//std::vector<u32> items{weapon, top, bottom, shoes, hair, face};
	//for (size_t i = 0; i < items.size(); i++) 
	//{
	//	if (!isLegal(items[i])) 
	//	{
	//		//FilePrinter.printError(FilePrinter.EXPLOITS + name + ".txt", "Owner from account '" + c.getAccountName() + "' tried to packet edit in char creation.");
	//		player->disconnect();
	//		return;
	//	}
	//}

	// KoC and Aran arent available in v62
	//if (job == 0) 
	//{ // Knights of Cygnus
	//	status = NoblesseCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
	//}
	//else if (job == 1)
	//{ // Adventurer
	//	status = BeginnerCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
	//}
	//else if (job == 2)
	//{ // Aran
	//	status = LegendCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
	//}
	//else 
	//{
	//	c.announce(PacketCreator::deleteCharacterResponse(0, 9));
	//	return;
	//}

	//u32 status = BeginnerCreator.createCharacter(player, name, face, hair + haircolor, skincolor, top, bottom, shoes, weapon, gender);
	//if (status == -2) {
	//	player->send(PacketCreator::deleteCharacterResponse(0, 9));
	//}
}
//
//bool isLegal(u32 toCompare)
//{
//	return false;
//	//return IDs.contains(toCompare);
//}