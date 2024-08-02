#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    Packet getLoginFailed(u32 reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeInt(packet, reason);
        util::PacketTool::writeShort(packet, 0);
        return packet;
    }

    Packet getPermBan(u32 reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeShort(packet, 2); // Account is banned
        util::PacketTool::writeInt(packet, 0);
        util::PacketTool::writeShort(packet, reason);
        util::PacketTool::writeByteArray(packet, { 0x8C, 0x65, 0x3F, 0x8A, 0xCB, 0xD1, 0x01 });
        return packet;
    }

    Packet getTempBan(u64 timestampTill, byte reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeByte(packet, 0x02);
        util::PacketTool::writeByteArray(packet, { 0x00, 0x00, 0x00, 0x00, 0x00 }); // Account is banned
        util::PacketTool::writeByte(packet, reason);
        util::PacketTool::writeLong(packet, timestampTill); // Tempban date is handled as a 64-bit long, number of 100NS intervals since 1/1/1601. Lulz.
        return packet;
    }

    Packet getLoginSuccess(std::string username)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeByteArray(packet, { 0, 0, 0, 0, 0, 0, (byte)0xFF, 0x6A, 1, 0, 0, 0, 0x4E });
        util::PacketTool::writeMapleString(packet, username);
        util::PacketTool::writeByteArray(packet, { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (byte)0xDC, 0x3D, 0x0B, 0x28, 0x64, (byte)0xC5, 1, 8, 0, 0, 0 });
        return packet;
    }

    //static Packet getLoginSuccess(std::shared_ptr<Player> player) 
    //{
    //    Server.getInstance().loadAccountCharacters(player);    // locks the login session until data is recovered from the cache or the DB.
    //    Server.getInstance().loadAccountStorages(player);

    //    final MaplePacketLittleEndianWriter mplew = new MaplePacketLittleEndianWriter();
    //    mplew.writeShort(SendOpcode.LOGIN_STATUS.getValue());
    //    mplew.writeInt(0);
    //    mplew.writeShort(0);
    //    mplew.writeInt(player.getAccID());
    //    mplew.write(player.getGender());

    //    boolean canFly = Server.getInstance().canFly(c.getAccID());
    //    mplew.writeBool((YamlConfig.config.server.USE_ENFORCE_ADMIN_ACCOUNT || canFly) ? c.getGMLevel() > 1 : false);    // thanks Steve(kaito1410) for pointing the GM account boolean here
    //    mplew.write(((YamlConfig.config.server.USE_ENFORCE_ADMIN_ACCOUNT || canFly) && c.getGMLevel() > 1) ? 0x80 : 0);  // Admin Byte. 0x80,0x40,0x20.. Rubbish.
    //    mplew.write(0); // Country Code.

    //    mplew.writeMapleAsciiString(c.getAccountName());
    //    mplew.write(0);

    //    mplew.write(0); // IsQuietBan
    //    mplew.writeLong(0);//IsQuietBanTimeStamp
    //    mplew.writeLong(0); //CreationTimeStamp

    //    mplew.writeInt(1); // 1: Remove the "Select the world you want to play in"

    //    mplew.write(YamlConfig.config.server.ENABLE_PIN && !c.canBypassPin() ? 0 : 1); // 0 = Pin-System Enabled, 1 = Disabled
    //    mplew.write(YamlConfig.config.server.ENABLE_PIC && !c.canBypassPic() ? (c.getPic() == null || c.getPic().equals("") ? 0 : 1) : 2); // 0 = Register PIC, 1 = Ask for PIC, 2 = Disabled

    //    return mplew.getPacket();
    //}
}