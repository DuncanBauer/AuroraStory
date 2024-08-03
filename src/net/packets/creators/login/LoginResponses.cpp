#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Gets a successful authentication and PIN Request packet.
     *
     * @param username The account name.
     * @return The PIN request packet.
     */
    Packet getLoginSuccess(std::string username)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeByteArray(packet, { 0, 0, 0, 0, 0, 0, (byte)0xFF, 0x6A, 1, 0, 0, 0, 0x4E });
        util::PacketTool::writeMapleString(packet, username);
        util::PacketTool::writeByteArray(packet, { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (byte)0xDC, 0x3D, 0x0B, 0x28, 0x64, (byte)0xC5, 1, 8, 0, 0, 0 });
        return packet;
    }

    /**
     * Gets a login failed packet.
     *
     * Possible values for <code>reason</code>:<br>
     * 3: ID deleted or blocked<br>
     * 4: Incorrect password<br>
     * 5: Not a registered id<br>
     * 6: System error<br>
     * 7: Already logged in<br>
     * 8: System error<br>
     * 9: System error<br>
     * 10: Cannot process so many connections<br>
     * 11: Only users older than 20 can use this channel<br>
     * 13: Unable to log on as master at this ip<br>
     * 14: Wrong gateway or personal info and weird korean button<br>
     * 15: Processing request with that korean button!<br>
     * 16: Please verify your account through email...<br>
     * 17: Wrong gateway or personal info<br>
     * 21: Please verify your account through email...<br>
     * 23: License agreement<br>
     * 25: Maple Europe notice =[<br>
     * 27: Some weird full client notice, probably for trial versions<br>
     *
     * @param reason The reason logging in failed.
     * @return The login failed packet.
     */
    Packet getLoginFailed(u32 reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeInt(packet, reason);
        util::PacketTool::writeShort(packet, 0);
        return packet;
    }

    /**
     * Banned reasons.
     *
     * 00 - Block user
     * 01 - Hacking
     * 02 - Botting
     * 03 - Advertising
     * 04 - Harassment
     * 05 - Profane language
     * 06 - Scamming
     * 07 - Misconduct
     * 08 - Illegal cash transaction
     * 09 - Illegal charging/funding
     * 10 - Temporary request
     * 11 - Impersonating GM
     * 12 - Violating game policy
     * 13 - Abusing Megaphones
     * @return
     */
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