#include <algorithm>
#include <ranges>

#include "Party.h"
#include "Player.h"

Party::Party(Character leader)
{
    PartyMember newMember;
    newMember.characterId = leader.getCharacterId();
    newMember.name = leader.getCharacterName();
    newMember.level = leader.getLevel();
    newMember.job = leader.getJob();
    newMember.channel = leader.getChannel();
    newMember.mapId = leader.getMapId();
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
    newMember.characterId = member.getCharacterId();
    newMember.name = member.getCharacterName();
    newMember.level = member.getLevel();
    newMember.job = member.getJob();
    newMember.channel = member.getChannel();
    newMember.mapId = member.getMapId();
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