#pragma once

#include "game/Character.h"
#include "net/asio/TCPConnection.h"
#include "MapleConstants.h"

using asio::ip::tcp;

struct Account
{
    u32         accountId      = 0;
    std::string username       = "";
    std::string pin            = "";
    i64         birthday       = 0;
    u32         isLoggedIn     = false;
    bool        isGM           = false;
    bool        isGuestAccount = false;
    bool        isBanned       = false;
    u32         banReason      = 1;
    i64         tempban        = 0;
};

class Player : public net::TCPConnection
{
public:
    Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets);
    ~Player();

    void                   processPacket(Packet& packet);
    
    void                   loadAccountData(bsoncxx::v_noabi::document::value const& data);
    std::vector<Character> loadCharacters(u32 serverId);
    void                   autoRegister(std::string const& username, std::string const& password);
    void                   banAccount();
    u32                    login(std::string const& username, std::string const& password, bsoncxx::v_noabi::document::value const& data);
    u32                    logout();
    bool                   checkPin(std::string pin);
    u32                    changeChannel();

    inline void            setWorld(u32 val)              { m_world = val; }
    inline void            setChannel(u32 val)            { m_channel = val; }
           void            setPin(std::string val);

    inline Account         getAccount()             const { return m_account;}
    inline u32             getWorld()               const { return m_world; }
    inline u32             getChannel()             const { return m_channel; }
    inline u32             getId()                  const { return m_account.accountId; }
    inline std::string     getPin()                 const { return m_account.pin; }
    inline bool            isGM()                   const { return m_account.isGM; }
    inline bool            isLoggedIn()             const { return m_account.isLoggedIn; }
    inline bool            isGuestAccount()         const { return m_account.isGuestAccount; }
    inline bool            isAccountBanned()        const { return m_account.isBanned; }
           bool            hasBannedIP()            const; 
           bool            hasBannedMAC()           const;


private:
    Account   m_account;
    u32       m_attemptedLogins = 0;
    u64       m_lastPong        = 0;
    u32       m_world           = 0;
    u32       m_channel         = 0;
    Character m_character;
};