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

struct Account
{
    std::string accountId;
    std::string username;
    std::string pin;
    i64 birthday = 0;
    u32 isLoggedIn = false;
    bool isGM = false;
    bool isGuestAccount = false;
    bool isBanned = false;
    u32 banReason = 1;
    i64 tempban = 0;
};

class Player : public net::TCPConnection
{
public:
    Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
    ~Player();

    void processPacket(Packet& packet);
    void loadAccountData(const bsoncxx::v_noabi::document::value& data);

    void autoRegister(const std::string& username, const std::string& password);
    void banAccount();

    u16 login(const std::string& username, const std::string& password, const bsoncxx::v_noabi::document::value& data);
    u32 logout();

    std::string getPin();
    void setPin(std::string pin);
    bool checkPin(std::string pin);

    u32 changeChannel();

    
    bool isGM();
    bool isLoggedIn();
    bool isGuestAccount();
    bool isAccountBanned();
    bool hasBannedIP();
    bool hasBannedMAC();

private:
    u16 m_attemptedLogins = 0;
    u64 m_lastPong = 0;

    Account m_account;
    Character m_character;
};