#pragma once

#include "asio.hpp"

#include "net/packets/PacketHandler.h"
#include "game/World.h"

struct DbSettings
{
    std::string mongoURI;
    std::string mongoDB;
};

struct ServerRates
{
    u16 expRate;
    u16 mesoRate;
    u16 dropRate;
    u16 partyExpRate;
    u16 partyMesoRate;
    u16 partyDropRate;
    u16 bossExpRate;
    u16 bossMesoRate;
    u16 bossDropRate;
    u16 questExpRate;
    u16 questMesoRate;
    u16 pqExpRate;
    u16 petExpRate;
};

struct EventSettings
{
    bool kerningPQEnabled;
    bool ludibriumPQEnabled;
    bool orbisPQEnabled;
    bool ludibriumMazePQEnabled;
};

struct ServerSettings
{
    u16 gameVersion;
    u16 channelCount;
    u16 loginServerInterval;
    u16 rankingInterval;
    bool guestLoginEnabled;
    bool autoRegisterEnabled;
    bool picEnabled;
    bool pinEnabled;
    u16 serverFlag;
    std::string serverMessage;
    std::string eventMessage;
    u16 maxPlayers;

    DbSettings dbSettings;
    ServerRates rates;
    EventSettings eventSettings;
};

class Master
{
public:
    Master();
    ~Master();

    void initialize();
    void run();
    void stop();

    static inline ServerSettings& getServerSettings() { return m_serverSettings; }
    static inline std::vector<std::string> getBannedIPs() { return m_bannedIPs; }
    static inline std::vector<std::string> getBannedMACs() { return m_bannedMACs; }

private:
    asio::io_context m_ioContext;
    
    static inline ServerSettings m_serverSettings;
    static inline std::vector<std::string> m_bannedIPs;
    static inline std::vector<std::string> m_bannedMACs;

    std::shared_ptr<LoginServer> m_loginServer;
    std::vector<std::shared_ptr<ChannelServer>> m_channelServers;
};