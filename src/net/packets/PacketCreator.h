#pragma once

#include <cstdint>
#include <string>

#include "net/packets/PacketConstants.h"
#include "util/PacketTool.h"
#include "util/LoggingTool.h"
#include "Typedefs.h"

class PacketCreator
{
public:
    PacketCreator() = delete;

    /*
    * Sends the handshake packet
    */
    static Packet getHandshake(Packet iv_recv, Packet iv_send);

    /**
     * Sends a ping packet.
     *
     * @return The packet.
     */
    static Packet getPing()
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_PING);
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
    static Packet getLoginFailed(u32 reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeInt(packet, reason);
        util::PacketTool::writeShort(packet, 0);
        SERVER_INFO("{}", util::PacketTool::outputPacketDec(packet).str());
        SERVER_INFO("{}", util::PacketTool::outputPacketHex(packet).str());
        SERVER_INFO("{}", util::PacketTool::outputPacketString(packet).str());
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
    static Packet getPermBan(u32 reason)
    {
        // [00 00] [02 00] [00 00 00 00] [01 00] [8C 65 3F 8A CB D1 01]
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeShort(packet, 2); // Account is banned
        util::PacketTool::writeInt(packet, 0);
        util::PacketTool::writeShort(packet, reason);
        util::PacketTool::writeByteArray(packet, { 0x8C, 0x65, 0x3F, 0x8A, 0xCB, 0xD1, 0x01 });
        return packet;
    }

    static Packet getTempBan(u64 timestampTill, byte reason)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeByte(packet, 0x02);
        util::PacketTool::writeByteArray(packet, { 0x00, 0x00, 0x00, 0x00, 0x00 }); // Account is banned
        util::PacketTool::writeByte(packet, reason);
        util::PacketTool::writeLong(packet, timestampTill); // Tempban date is handled as a 64-bit long, number of 100NS intervals since 1/1/1601. Lulz.
        return packet;
    }

    /**
     * Gets a successful authentication and PIN Request packet.
     *
     * @param username The account name.
     * @return The PIN request packet.
     */
    static Packet getLoginSuccess(std::string username) 
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_LOGIN_STATUS);
        util::PacketTool::writeByteArray(packet, { 0, 0, 0, 0, 0, 0, (byte)0xFF, 0x6A, 1, 0, 0, 0, 0x4E });
        util::PacketTool::writeMapleString(packet, username);
        util::PacketTool::writeByteArray(packet, { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (byte)0xDC, 0x3D, 0x0B, 0x28, 0x64, (byte)0xC5, 1, 8, 0, 0, 0 });
        return packet;
    }

    //static Packet getAuthSuccess(std::shared_ptr<Player> player) 
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


    /**
     * Gets a packet detailing a PIN operation.
     *
     * Possible values for <code>mode</code>:<br>
     * 0 - PIN was accepted<br>
     * 1 - Register a new PIN<br>
     * 2 - Invalid pin / Reenter<br>
     * 3 - Connection failed due to system error<br>
     * 4 - Enter the pin
     *
     * @param mode The mode.
     */
    static Packet pinOperation(byte mode) 
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_PIN_OPERATION);
        util::PacketTool::writeByte(packet, mode);
        return packet;
    }

    /**
     * Gets a packet requesting the client enter a PIN.
     *
     * @return The request PIN packet.
     */
    static Packet requestPin() 
    {
        return pinOperation((byte)4);
    }

    /**
     * Gets a packet requesting the PIN after a failed attempt.
     *
     * @return The failed PIN packet.
     */
    static Packet requestPinAfterFailure() 
    {
        return pinOperation((byte)2);
    }

    /**
     * Gets a packet saying the PIN has been accepted.
     *
     * @return The PIN accepted packet.
     */
    static Packet pinAccepted() 
    {
        return pinOperation((byte)0);
    }
};