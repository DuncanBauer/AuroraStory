#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet characterCreationSuccess(Character character)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, Constants::SendOps::k_ADD_NEW_CHAR_ENTRY);
        util::PacketTool::writeIntAsByte(packet, 0);
        addCharacterEntry(packet, character);
        return packet;
    }

    /**
     * State :
     * 0x00 = success
     * 0x06 = Trouble logging into the game?
     * 0x09 = Unknown error
     * 0x0A = Could not be processed due to too many connection requests to the server.
     * 0x12 = invalid bday
     * 0x14 = incorrect pic
     * 0x16 = Cannot delete a guild master.
     * 0x18 = Cannot delete a character with a pending wedding.
     * 0x1A = Cannot delete a character with a pending world transfer.
     * 0x1D = Cannot delete a character that has a family.
     *
     * @param cid
     * @param state
     * @return
     */
    Packet characterCreationFailed(u32 cid, u32 state)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, Constants::SendOps::k_DELETE_CHAR_RESPONSE);
        util::PacketTool::writeInt(packet, cid);
        util::PacketTool::writeByte(packet, state);
        return packet;
    }
}