#pragma once

#include <cstdint>

namespace net
{
    struct WorldSettings
    {
        uint16_t flag;
        std::string serverMessage;
        std::string eventMessage;
        uint16_t channelCount;
        uint16_t maxPlayers;
        bool kerningPQEnabled;
        bool ludibriumPQEnabled;
        bool orbisPQEnabled;
        bool ludibriumMazePQEnabled;
    };

    struct WorldRates
    {
        uint16_t expRate;
        uint16_t mesoRate;
        uint16_t dropRate;
        uint16_t partyExpRate;
        uint16_t partyMesoRate;
        uint16_t partyDropRate;
        uint16_t pqExpRate;
        uint16_t bossExpRate;
        uint16_t bossMesoRate;
        uint16_t bossDropRate;
        uint16_t questExpRate;
        uint16_t questMesoRate;
        uint16_t petExpRate;
    };

    class World
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
}