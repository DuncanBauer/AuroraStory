#pragma once

#include "net/asio/TCPConnection.h"
#include "MapleConstants.h"

using asio::ip::tcp;

struct Character
{
    std::string characterId;
    std::string characterName;
    u16 job;
    u16 level;
    std::atomic<u64> exp;
    std::atomic<u64> mesos;
    i32 fame;

    // Stats
    u32 unspentAp, unspentSp;
    u32 hpApUsed, mpApUsed;
    u32 currentHp, maxHp, localMaxHp;
    u32 currentMp, maxMp, localMaxMp;
    u32 baseStr, localStr;
    u32 baseDex, localDex;
    u32 baseLuk, localLuk;
    u32 baseInt, localInt;
    u32 magic, watk;
    float speedModifier, jumpModifier;

    // Appearance
    u32 genderId;
    u32 faceId;
    u32 hairId;
    u32 skinId;

    u16 channel;
    u32 mapId;

    //// Misc
    //Map map;
    //Keymap keymap;
    //Buffs buffs;
    //Diseases diseases;
    //Skills skills;
    //Inventory inventory;
    //EquipInventory equipInventory;
    //Storage storage;
    //Quests quests;
    //Trade trade;
    //PlayerShop shop;
    //BuddyList buddyList;
    //Party party;
    //Guild guild;
    //Messenger messenger;
};

class Player : public net::TCPConnection
{
public:
    Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
    ~Player();

    void processPacket(Packet& packet);
    void loadAccountData();

    u32 login(const std::string& username, const std::string& password);
    u32 logout();
    u32 changeChannel();

    void banAccount();
    
    bool isGM();
    bool isLoggedIn();
    bool isGuestAccount();
    bool isAccountBanned();
    bool hasBannedIp();
    bool hasBannedMac();

private:
    std::string m_accountId;
    std::string m_accountName;
    Calendar m_birthday = {};
    bool m_isLoggedIn = false;
    bool m_isGM = false;
    bool m_isGuestAccount = false;
    bool m_isBanned = false;
    byte m_banReason = 1;
    Calendar m_tempban = {};
    u16 m_attemptedLogins = 0;
    u64 m_lastPong = 0;

    Character m_character;
};