#pragma once

#include <string>
#include <vector>

#include "game/Character.h"
#include "MapleConstants.h"
#include "Typedefs.h"

struct PartyMember
{
    std::string characterId;
    std::string name;
    u16 level;
    u16 job;
    u16 channel;
    u32 mapId;
    bool online;

    u32 mysticDoorTown;
    u32 mysticDoorTargetMap;
    Point mysticDoorPosition;

    inline const std::string getId() const { return characterId; }
    inline const std::string getName() const { return name; }
    inline const u16 getLevel() const { return level; }
    inline const u16 getJob() const { return job; }
    inline const u16 getChannel() const { return channel; }
    inline const u32 getMapId() const { return mapId; }
    inline const bool isOnline() const { return online; }
    inline const u32 getMysticDoorTown() const { return mysticDoorTown; }
    inline const u32 getMysticDoorTargetMap() const { return mysticDoorTargetMap; }
    inline const Point getMysticDoorPosition() const { return mysticDoorPosition; }

    inline bool operator==(const PartyMember& other) const 
    {
        return characterId == other.characterId;
    }
};

class Party
{
public:
    Party(Character leader);
    ~Party();

    bool addMember(Character& member);
    bool removeMember(std::string characterId);
    bool removeMember(PartyMember member);

private:
    std::string m_id;
    PartyMember m_leader;
    std::vector<PartyMember> m_members;
};

