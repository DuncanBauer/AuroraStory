#include "pch.h"

#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    void PacketHandler::handlePlayerDC(Packet& packet)
    {
        SERVER_INFO("PacketHandler::handlePlayerDC");

        uint16_t loginOk = 0;
    }
}