#include <algorithm>
#include <ranges>

#include "Party.h"
#include "Player.h"

Party::Party(Character leader)
{
    PartyMember newMember;
    newMember.characterId = leader.characterId;
    newMember.name = leader.characterName;
    newMember.level = leader.level;
    newMember.job = leader.job;
    newMember.channel = leader.channel;
    newMember.mapId = leader.mapId;
    newMember.online = true;

    //if (leader.getDoors().size() > 0) {
    //    newMember.mysticDoorTown = leader.getDoors().get(0).getTown().getId();
    //    newMember.mysticDoorTargetMap = leader.getDoors().get(0).getTarget().getId();
    //    newMember.mysticDoorPosition = leader.getDoors().get(0).getTargetPosition();
    //}

    m_leader = newMember;
    m_members.push_back(newMember);
}

Party::~Party()
{

}

bool Party::addMember(Character& member)
{
    PartyMember newMember;
    newMember.characterId = member.characterId;
    newMember.name = member.characterName;
    newMember.level = member.level;
    newMember.job = member.job;
    newMember.channel = member.channel;
    newMember.mapId = member.mapId;
    newMember.online = true;

    //if (member.getDoors().size() > 0) {
    //    newMember.mysticDoorTown = member.getDoors().get(0).getTown().getId();
    //    newMember.mysticDoorTargetMap = member.getDoors().get(0).getTarget().getId();
    //    newMember.mysticDoorPosition = member.getDoors().get(0).getTargetPosition();
    //}

    if (m_members.size() < 6)
    {
        m_members.push_back(newMember);
    }
    return false;
}

bool Party::removeMember(std::string characterId)
{
    auto it = std::ranges::find_if(m_members, [&characterId](const PartyMember& member) 
    {
        return member.characterId == characterId;
    });

    if (it != m_members.end())
    {
        m_members.erase(it);
    }
    return false;
}

bool Party::removeMember(PartyMember member)
{
    auto it = std::find(m_members.begin(), m_members.end(), member);
    if (it != m_members.end())
    {
        m_members.erase(it);
    }
    return false;
}