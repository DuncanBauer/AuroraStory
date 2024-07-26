#pragma once

#include <cstdint>

namespace net
{
    struct WorldSettings
    {
        uint16_t worldCount;
        bool kerningPQEnabled;
        bool ludiPQEnabled;
        bool orbisPQEnabled;
        bool ludimazePQEnabled;
    };

    struct WorldRates
    {
        uint16_t expRate;
        uint16_t mesoRate;
        uint16_t dropRate;
        uint16_t partyExpRate;
        uint16_t partyMesoRate;
        uint16_t partyDropRate;
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

    private:
        WorldSettings m_settings;
        WorldRates m_rates;
    };
}