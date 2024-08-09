#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet checkCharacterNameResponse(std::string characterName, bool isUsed)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_CHAR_NAME_RESPONSE);
        util::PacketTool::writeMapleString(packet, characterName);
        util::PacketTool::writeIntAsByte(packet, isUsed ? 1 : 0);
        return packet;
    }
}