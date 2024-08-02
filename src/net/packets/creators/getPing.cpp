#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet getPing()
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_PING);
        return packet;
    }
}