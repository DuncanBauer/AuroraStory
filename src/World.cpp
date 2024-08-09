#include <memory>

#include "Master.h"
#include "World.h"

World::World(WorldSettings settings)
{
    m_settings = settings;
}

World::~World()
{

}

void World::startChannels(u16& channelPort)
{
    for (u16 i = 0; i < m_settings.channelCount; i++)
    {
        m_channelServers.push_back(std::make_shared<ChannelServer>(Master::getInstance().getIoContext(), channelPort++));
        m_channelServers[i]->start();
    }
}

std::map<u32, u32> World::getChannelLoads()
{
    std::map<u32, u32> loads;
    for (u16 i = 0; i < m_channelServers.size(); i++)
    {
        loads[i + 1] = m_channelServers[i]->getUserLoad();
    }
    return loads;
}

void World::addCharacterToAccount(u32 accountId, u32 characterId)
{
    m_accountCharacterIds[accountId].insert(characterId);
}

void World::removeCharacterToAccount(u32 accountId, u32 characterId)
{
    m_accountCharacterIds[accountId].erase(characterId);
}