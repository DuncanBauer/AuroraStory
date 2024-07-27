

#include "World.h"

namespace net
{
    World::World()
    {

    }

    World::~World()
    {

    }

    void World::initialize()
    {

    }

    WorldSettings& World::getSettings()
    {
        return m_settings;
    }
    
    WorldRates& World::getRates()
    {
        return m_rates;
    }
}