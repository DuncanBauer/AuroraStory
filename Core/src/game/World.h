#pragma once

#include <string>

#include "Core.h"
#include "Typedefs.h"

struct WorldSettings
{
    u16 flag;
    std::string serverMessage;
    std::string eventMessage;
    u16 channelCount;
    u16 maxPlayers;
    bool kerningPQEnabled;
    bool ludibriumPQEnabled;
    bool orbisPQEnabled;
    bool ludibriumMazePQEnabled;
};

struct WorldRates
{
    u16 expRate;
    u16 mesoRate;
    u16 dropRate;
    u16 partyExpRate;
    u16 partyMesoRate;
    u16 partyDropRate;
    u16 pqExpRate;
    u16 bossExpRate;
    u16 bossMesoRate;
    u16 bossDropRate;
    u16 questExpRate;
    u16 questMesoRate;
    u16 petExpRate;
};

class AURORA_SERVER_API World
{
public:
    World();
    ~World();

    void initialize();

    WorldSettings& getSettings();
    WorldRates& getRates();

private:
    WorldSettings m_settings;
    WorldRates m_rates;
};