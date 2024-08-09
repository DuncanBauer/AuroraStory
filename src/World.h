#pragma once

#include <string>
#include <unordered_set>

#include "net/channel/ChannelServer.h"
#include "Typedefs.h"

struct WorldRates
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

struct WorldSettings
{
    u32         worldId;
    u32         serverFlag;
    std::string serverMessage;
    std::string eventMessage;
    u16         channelCount;
    u16         maxPlayers;
    WorldRates  rates;
};

class World
{
public:
    World(WorldSettings settings);
    World(const World&) = delete;
    World(World&&)      = delete;
    ~World();

           void               startChannels(u16& channelPort);

    inline WorldSettings&     getSettings()                               { return m_settings; }
    inline size_t             getChannelCount()                           { return m_channelServers.size(); }
           std::map<u32, u32> getChannelLoads();                          
    inline u32                getChannelLoad(u32 channelId)               { return m_channelServers[channelId]->getUserLoad(); }

    inline std::unordered_set<u32> getAccountCharacterIds(u32 accountId)  { return m_accountCharacterIds[accountId]; }
           void               addCharacterToAccount(u32 accountId, u32 characterId);
           void               removeCharacterToAccount(u32 accountId, u32 characterId);
    inline size_t             getAccountCharacterCount(u32 accountId)     { return m_accountCharacterIds[accountId].size(); }

private:
    WorldSettings                               m_settings;

    std::vector<std::shared_ptr<ChannelServer>> m_channelServers;
    std::map<u32, std::thread>                  m_channelServerThreads;

    std::map<u32, std::unordered_set<u32>>      m_accountCharacterIds;
};