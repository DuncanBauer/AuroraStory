#pragma once

#include <cstdint>
#include <string>

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

};