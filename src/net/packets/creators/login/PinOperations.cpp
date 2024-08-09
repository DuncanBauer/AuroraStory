#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Gets a packet detailing a PIN operation.
     *
     * Possible values for <code>mode</code>:<br>
     * 0 - PIN was accepted<br>
     * 1 - Register a new PIN<br>
     * 2 - Invalid pin / Reenter<br>
     * 3 - Connection failed due to system error<br>
     * 4 - Enter the pin
     *
     * @param mode The mode.
     */
    Packet pinOperation(byte mode)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, Constants::SendOps::k_PIN_OPERATION);
        util::PacketTool::writeByte(packet, mode);
        return packet;
    }

    /**
     * Gets a packet saying the PIN has been accepted.
     *
     * @return The PIN accepted packet.
     */
    Packet pinAccepted()
    {
        return pinOperation((byte)0);
    }

    /**
     * Gets a packet saying the PIN has been registered.
     *
     * @return The PIN registered packet.
     */
    Packet registerPin()
    {
        return pinOperation((byte)1);
    }

    /**
     * Gets a packet requesting the client enter a PIN.
     *
     * @return The request PIN packet.
     */
    Packet requestPin()
    {
        return pinOperation((byte)4);
    }

    /**
     * Gets a packet requesting the PIN after a failed attempt.
     *
     * @return The failed PIN packet.
     */
    Packet requestPinAfterFailure()
    {
        return pinOperation((byte)2);
    }
}