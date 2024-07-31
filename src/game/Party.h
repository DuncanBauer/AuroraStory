#pragma once

#include <string>
#include <vector>

#include "MapleConstants.h"
#include "Typedefs.h"

struct Character;

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

    inline std::string getId() { return characterId; }
    inline std::string getName() { return name; }
    inline u16 getLevel() { return level; }
    inline u16 getJob() { return job; }
    inline u16 getChannel() { return channel; }
    inline u32 getMapId() { return mapId; }
    inline bool isOnline() { return online; }
    inline u32 getMysticDoorTown() { return mysticDoorTown; }
    inline u32 getMysticDoorTargetMap() { return mysticDoorTargetMap; }
    inline Point getMysticDoorPosition() { return mysticDoorPosition; }

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

