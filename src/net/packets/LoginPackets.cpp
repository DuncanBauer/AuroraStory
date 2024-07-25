#include "PacketCreator.h"
#include "MapleConstants.h"

namespace net
{
    void PacketCreator::getHandshake(std::vector<byte> iv_recv, std::vector<byte> iv_send)
    {
        writeShort(k_packetHandshakeServerLength + static_cast<short>(k_gameMinorVersion.length()));
        writeShort(k_gameVersion);
        writeString(k_gameMinorVersion);
        writeInt(*(int*)iv_recv.data());
        writeInt(*(int*)iv_send.data());
        writeSByte(k_gmsLocale);
    }
}