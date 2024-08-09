#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Sends a ping packet.
     *
     * @return The packet.
     */
    Packet getPing()
    {
        Packet packet;
        util::PacketTool::writeShort(packet, Constants::SendOps::k_PING);
        return packet;
    }
}