#include <set>

#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet getServerStatus(u16 status)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_SERVER_STATUS);
        util::PacketTool::writeShort(packet, status);
        return packet;
    }
}