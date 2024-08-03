#pragma once

#include <string>
#include "Typedefs.h"

#include "net/channel/ChannelServer.h"

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
    u32 serverFlag;
    std::string serverMessage;
    std::string eventMessage;
    u16 channelCount;
    u16 maxPlayers;

    WorldRates rates;
};

class World
{
public:
    World(WorldSettings settings);
    ~World();

    inline WorldSettings& getSettings() { return m_settings; }

    void startChannels(u16& channelPort);
    inline u32 getChannelCount() { return (u32)m_channelServers.size(); }
    std::map<u32, u32> getChannelLoads();

private:
    WorldSettings m_settings;

    std::vector<std::shared_ptr<ChannelServer>> m_channelServers;
    std::map<int, std::thread> m_channelServerThreads;
};