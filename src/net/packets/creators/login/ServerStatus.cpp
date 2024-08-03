#include <set>

#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Gets a packet detailing a server status message.
     *
     * Possible values for <code>status</code>:<br>
     * 0 - Normal<br>
     * 1 - Highly populated<br>
     * 2 - Full
     *
     * @param status The server status.
     * @return The server status packet.
     */
    Packet getServerStatus(u16 status)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_SERVER_STATUS);
        util::PacketTool::writeShort(packet, status);
        return packet;
    }
}