#include "net/packets/PacketCreator.h"
#include "util/PacketTool.h"
#include "MapleConstants.h"

Packet PacketCreator::getHandshake(Packet iv_recv, Packet iv_send)
{
    Packet packet;
    util::PacketTool::writeShort(packet, 14);
    util::PacketTool::writeShort(packet, k_gameVersion);
    util::PacketTool::writeShort(packet, k_gameMinorVersion);
    util::PacketTool::writeByte(packet, 49);
    util::PacketTool::writeInt(packet, *(int*)iv_recv.data());
    util::PacketTool::writeInt(packet, *(int*)iv_send.data());
    util::PacketTool::writeByte(packet, k_gmsLocale);
    return packet;
}