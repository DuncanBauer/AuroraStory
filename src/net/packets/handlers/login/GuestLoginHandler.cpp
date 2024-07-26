#include "pch.h"

#include "util/Logger.h"
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

    void PacketHandler::handleGuestLogin(Packet& packet)
    {
        SERVER_INFO("PacketHandler::handleGuestLogin");

        uint16_t loginOk = 0;
    }
}