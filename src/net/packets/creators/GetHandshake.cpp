#include "net/packets/PacketCreator.h"
#include "util/PacketTool.h"
#include "constants/MapleConstants.h"

Packet PacketCreator::getHandshake(Packet iv_recv, Packet iv_send)
{
    /*
    * Sends the handshake packet
    */
    Packet packet;
    util::PacketTool::writeShort(packet, 14);
    util::PacketTool::writeShort(packet, Constants::Maple::k_gameVersion);
    util::PacketTool::writeShort(packet, Constants::Maple::k_gameMinorVersion);
    util::PacketTool::writeByte(packet, 49);
    util::PacketTool::writeInt(packet, *(int*)iv_recv.data());
    util::PacketTool::writeInt(packet, *(int*)iv_send.data());
    util::PacketTool::writeByte(packet, Constants::Maple::k_gmsLocale);
    return packet;
}