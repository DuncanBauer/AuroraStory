#include "net/packets/PacketCreator.h"

#include "constants/MapleConstants.h"

namespace net
{
    std::vector<byte> PacketCreator::getHandshake(std::vector<byte> iv_recv, std::vector<byte> iv_send)
    {
        std::vector<byte> packet;
        writeShort(packet, 14);
        writeShort(packet, constant::k_gameVersion);
        writeShort(packet, constant::k_gameMinorVersion);
        writeSByte(packet, 49);
        writeInt(packet, *(int*)iv_recv.data());
        writeInt(packet, *(int*)iv_send.data());
        writeSByte(packet, constant::k_gmsLocale);
        return packet;
    }
}