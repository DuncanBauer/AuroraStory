#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet pinOperation(byte mode)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_PIN_OPERATION);
        util::PacketTool::writeByte(packet, mode);
        return packet;
    }

    Packet pinRegistered()
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_PIN_OPERATION);
        util::PacketTool::writeByte(packet, 0);
        return packet;
    }

    Packet pinAccepted()
    {
        return pinOperation((byte)0);
    }

    Packet registerPin()
    {
        return pinOperation((byte)1);
    }

    Packet requestPin()
    {
        return pinOperation((byte)4);
    }

    Packet requestPinAfterFailure()
    {
        return pinOperation((byte)2);
    }
}