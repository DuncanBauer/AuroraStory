#include "pch.h"

#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    void PacketHandler::handleClientStart(Packet& packet)
    {
        SERVER_INFO("PacketHandler::handleClientStart");

        uint16_t loginOk = 0;
    }
}