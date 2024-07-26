#include "pch.h"

#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    void PacketHandler::handleServerStatusRequest(Packet& packet)
    {
        SERVER_INFO("PacketHandler::handleServerStatusRequest");

        uint16_t loginOk = 0;
    }
}