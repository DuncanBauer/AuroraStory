#pragma once

#include <cstdint>
#include <string>

#include "Typedefs.h"

class PacketCreator
{
public:
    PacketCreator() = delete;

    static Packet getHandshake(Packet iv_recv, Packet iv_send);
};