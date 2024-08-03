#include <set>

#include "Master.h"
#include "game/Inventory.h"
#include "net/packets/PacketCreator.h"
#include "util/MapleTool.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet characterNameResponse(std::string characterName, bool isUsed) {
        // 0D 00 0C 00 42 6C 61 62 6C 75 62 62 31 32 33 34 00
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_CHAR_NAME_RESPONSE);
        util::PacketTool::writeMapleString(packet, characterName);
        util::PacketTool::writeIntAsByte(packet, isUsed ? 1 : 0);
        return packet;
    }
}