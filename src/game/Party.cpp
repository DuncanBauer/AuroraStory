#include <algorithm>

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

bool Party::addMember(Character member)
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

    if (m_members.size() < 6)
        m_members.push_back(newMember);
}

bool Party::removeMember(Character member)
{
    PartyMember newMember;
    auto it = std::find(m_members.begin(), m_members.end(), newMember);
    if (it != m_members.end())
        m_members.erase(it);
}