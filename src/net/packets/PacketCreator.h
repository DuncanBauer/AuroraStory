#pragma once

#include <cstdint>
#include <string>

#include "net/packets/PacketConstants.h"
#include "util/PacketTool.h"
#include "util/LoggingTool.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /*
    * Sends the handshake packet
    */
    Packet getHandshake(Packet iv_recv, Packet iv_send);

    /**
     * Sends a ping packet.
     *
     * @return The packet.
     */
    Packet getPing();

    /**
     * Gets a successful authentication and PIN Request packet.
     *
     * @param username The account name.
     * @return The PIN request packet.
     */
    Packet getLoginSuccess(std::string username);

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
    Packet getLoginFailed(u32 reason);

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
    Packet getPermBan(u32 reason);
    Packet getTempBan(u64 timestampTill, byte reason);


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
    Packet pinOperation(byte mode);

    /**
     * Gets a packet saying the PIN has been accepted.
     *
     * @return The PIN accepted packet.
     */
    Packet pinAccepted();

    /**
     * Gets a packet saying the PIN has been registered.
     *
     * @return The PIN registered packet.
     */
    Packet registerPin();

    /**
     * Gets a packet requesting the client enter a PIN.
     *
     * @return The request PIN packet.
     */
    Packet requestPin();

    /**
     * Gets a packet requesting the PIN after a failed attempt.
     *
     * @return The failed PIN packet.
     */
    Packet requestPinAfterFailure();

    /**
     * Gets a packet detailing a server and its channels.
     *
     * @param serverIndex The index of the server to create information about.
     * @param serverName The name of the server.
     * @param channelLoad Load of the channel - 1200 seems to be max.
     * @return The server info packet.
     */
    Packet getServerData(u32 serverId, std::string serverName, std::map<u32, u32> channelLoad);

    /**
     * Gets a packet saying that the server list is over.
     *
     * @return The end of server list packet.
     */
    Packet getEndOfServerList();

    /**
     * Gets a packet detailing a server status message.
     *
     * Possible values for <code>status</code>:<br>
     * 0 - Normal<br>
     * 1 - Highly populated<br>
     * 2 - Full
     *
     * @param status The server status.
     * @return The server status packet.
     */
    Packet getServerStatus(u16 status);
};