#include "net/packets/PacketProcessor.h"

#include "MapleConstants.h"

Packet PacketProcessor::getHandshake(Packet iv_recv, Packet iv_send)
{
    Packet packet;
    writeShort(packet, 14);
    writeShort(packet, k_gameVersion);
    writeShort(packet, k_gameMinorVersion);
    writeSByte(packet, 49);
    writeInt(packet, *(int*)iv_recv.data());
    writeInt(packet, *(int*)iv_send.data());
    writeSByte(packet, k_gmsLocale);
    return packet;
}