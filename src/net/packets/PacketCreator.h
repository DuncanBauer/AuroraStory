#pragma once

#include <cstdint>
#include <string>

#include "net/packets/PacketConstants.h"
#include "util/PacketTool.h"
#include "util/LoggingTool.h"
#include "Typedefs.h"

class Character;

namespace PacketCreator
{
    Packet getHandshake(Packet iv_recv, Packet iv_send);

    Packet getPing();

    Packet getLoginSuccess(std::string username);
    Packet getLoginFailed(u32 reason);
    Packet getPermBan(u32 reason);
    Packet getTempBan(u64 timestampTill, byte reason);

    Packet pinOperation(byte mode);
    Packet pinAccepted();
    Packet registerPin();
    Packet requestPin();
    Packet requestPinAfterFailure();

    Packet getServerData(u32 serverId, std::string serverName, std::map<u32, u32> channelLoad);
    Packet getEndOfServerList();

    Packet getServerStatus(u16 status);

    Packet getCharacterList(std::shared_ptr<Player> player, u32 serverId);
    void   addCharacterEntry(Packet packet, Character character);
    void   addCharacterLook(Packet packet, Character character, bool mega);
    void   addCharacterStats(Packet packet, Character character);

    Packet characterNameResponse(std::string characterName, bool isUsed);
};