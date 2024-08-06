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
    u16         level;
    u16         job;
    u16         channel;
    u32         mapId;
    bool        online;

    u32         mysticDoorTown;
    u32         mysticDoorTargetMap;
    Point       mysticDoorPosition;

    inline std::string const getId()                  const { return characterId; }
    inline std::string const getName()                const { return name; }
    inline u16         const getLevel()               const { return level; }
    inline u16         const getJob()                 const { return job; }
    inline u16         const getChannel()             const { return channel; }
    inline u32         const getMapId()               const { return mapId; }
    inline bool        const isOnline()               const { return online; }
    inline u32         const getMysticDoorTown()      const { return mysticDoorTown; }
    inline u32         const getMysticDoorTargetMap() const { return mysticDoorTargetMap; }
    inline Point       const getMysticDoorPosition()  const { return mysticDoorPosition; }

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
    std::string              m_id      = 0;
    PartyMember              m_leader;
    std::vector<PartyMember> m_members;
};

