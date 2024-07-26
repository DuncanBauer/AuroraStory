#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    enum LoginStatus
    {
        LOGIN_SUCCESS,
        LOGIN_FAIL,
        BANNED
    };
    void PacketHandler::handleLoginPassword(Packet& packet)
    {
        std::string username = PacketCreator::readMapleString(packet);
        std::string password = PacketCreator::readMapleString(packet);

        uint16_t loginOk = 0;

        // if username exists
            // check ban status
            // check password hash
        // else
            // if auto register enabled
                // register
    }
}