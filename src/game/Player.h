#pragma once

#include "game/Character.h"
#include "net/asio/TCPConnection.h"
#include "MapleConstants.h"

using asio::ip::tcp;

struct Account
{
    u32 accountId;
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

    inline u16 getWorld() { return m_world; }
    inline u16 getChannel() { return m_channel; }

    inline void setWorld(u16 val) { m_world = val; }
    inline void setChannel(u16 val) { m_channel = val; }

    void processPacket(Packet& packet);
    void loadAccountData(const bsoncxx::v_noabi::document::value& data);
    std::vector<Character> loadCharacters(u32 serverId);

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

    u16 m_world;
    u16 m_channel;

    Account m_account;
    Character m_character;
};