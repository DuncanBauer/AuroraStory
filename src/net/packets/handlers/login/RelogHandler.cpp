#include "pch.h"

#include "util/Logger.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

namespace net
{
    void PacketHandler::handleRelog(Packet& packet)
    {
        SERVER_INFO("PacketHandler::handleRelog");

        uint16_t loginOk = 0;
    }
}