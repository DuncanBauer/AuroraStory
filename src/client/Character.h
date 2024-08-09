#pragma once

#include "constants/MapleConstants.h"
#include "Inventory.h"
#include "Typedefs.h"

class Character
{
public:
    Character();
    Character(u32 const accountId, u32 const worldId);
    Character(Character const& other);
    ~Character();

    bool        saveToDB();
    bool        loadFromDB();

    static bool canCreateCharacter(std::string const& name, u32 world);
    static u32  createCharacter(std::shared_ptr<Player> player, std::string name, 
                                u32 face,    u32 hair,    u32 hairColor, u32 skin, 
                                u32 top,     u32 bottom,  u32 shoes,     u32 weapon, u32 gender, 
                                u32 baseStr, u32 baseDex, u32 baseInt,   u32 baseLuk);

    static u32         const getCharacterIdByName(std::string name, u16 world);
    static std::string const getCharacterNameById(u32 id, u16 world);

    // Getters
    inline u32         const getAccountId()     const { return m_accountId; }
    inline u32         const getCharacterId()   const { return m_characterId; }
    inline u32         const getWorld()         const { return m_world; }
    inline u32         const getChannel()       const { return m_channel; }
    inline u32         const getMapId()         const { return m_mapId; }
    inline u32         const getSpawnpoint()    const { return m_spawnpoint; }
    inline std::string const getCharacterName() const { return m_characterName; }
    inline u32         const getGMLevel()       const { return m_gmLevel; }
    inline u32         const getJob()           const { return m_job; }
    inline u32         const getLevel()         const { return m_level; }
    inline i32         const getRank()          const { return m_rank; }
    inline i32         const getRankMove()      const { return m_rankMove; }
    inline i32         const getJobRank()       const { return m_jobRank; }
    inline i32         const getJobRankMove()   const { return m_jobRankMove; }
    inline u32         const getExp()           const { return m_exp.load(std::memory_order_relaxed); }
    inline u32         const getMesos()         const { return m_mesos.load(std::memory_order_relaxed); }
    inline i32         const getFame()          const { return m_fame; }
    inline u32         const getUnspentAp()     const { return m_unspentAp; }
    inline u32         const getUnspentSp()     const { return m_unspentSp; }
    inline u32         const getHpApUsed()      const { return m_hpApUsed; }
    inline u32         const getMpApUsed()      const { return m_mpApUsed; }
    inline u32         const getCurrentHp()     const { return m_currentHp; }
    inline u32         const getMaxHp()         const { return m_maxHp; }
    inline u32         const getLocalMaxHp()    const { return m_localMaxHp; }
    inline u32         const getCurrentMp()     const { return m_currentMp; }
    inline u32         const getMaxMp()         const { return m_maxMp; }
    inline u32         const getLocalMaxMp()    const { return m_localMaxMp; }
    inline u32         const getBaseStr()       const { return m_baseStr; }
    inline u32         const getLocalStr()      const { return m_localStr; }
    inline u32         const getBaseDex()       const { return m_baseDex; }
    inline u32         const getLocalDex()      const { return m_localDex; }
    inline u32         const getBaseLuk()       const { return m_baseLuk; }
    inline u32         const getLocalLuk()      const { return m_localLuk; }
    inline u32         const getBaseInt()       const { return m_baseInt; }
    inline u32         const getLocalInt()      const { return m_localInt; }
    inline u32         const getMagic()         const { return m_magic; }
    inline u32         const getWatk()          const { return m_watk; }
    inline float       const getSpeedModifier() const { return m_speedModifier; }
    inline float       const getJumpModifier()  const { return m_jumpModifier; }
    inline u32         const getGenderId()      const { return m_genderId; }
    inline u32         const getFaceId()        const { return m_faceId; }
    inline u32         const getHairId()        const { return m_hairId; }
    inline u32         const getSkinId()        const { return m_skinId; }

    Inventory&               getInventory(u32 const inventoryType);

    // Setters
    inline void setAccountId(u32 val)             { m_accountId = val; }
    inline void setCharacterId(u32 val)           { m_characterId = val; }
    inline void setWorld(u32 val)                 { m_world = val; }
    inline void setChannel(u32 val)               { m_channel = val; }
    inline void setMapId(u32 val)                 { m_mapId = val; }
    inline void setSpawnpoint(u32 val)            { m_spawnpoint = val; }
    inline void setCharacterName(std::string val) { m_characterName = val; }
    inline void setGMLevel(u32 val)               { m_gmLevel = val; }
    inline void setJob(u32 val)                   { m_job = val; }
    inline void setLevel(u32 val)                 { m_level = val; }
    inline void setRank(i32 val)                  { m_rank = val; }
    inline void setRankMove(i32 val)              { m_rankMove = val; }
    inline void setJobRank(i32 val)               { m_jobRank = val; }
    inline void setJobRankMove(i32 val)           { m_jobRankMove = val; }
    inline void setExp(u32 val)                   { m_exp.store(val, std::memory_order_relaxed); }
    inline void setMesos(u32 val)                 { m_mesos.store(val, std::memory_order_relaxed); }
    inline void setFame(i32 val)                  { m_fame = val; }
    inline void setUnspentAp(u32 val)             { m_unspentAp = val; }
    inline void setUnspentSp(u32 val)             { m_unspentSp = val; }
    inline void setHpApUsed(u32 val)              { m_hpApUsed = val; }
    inline void setMpApUsed(u32 val)              { m_mpApUsed = val; }
    inline void setCurrentHp(u32 val)             { m_currentHp = val; }
    inline void setMaxHp(u32 val)                 { m_maxHp = val; }
    inline void setLocalMaxHp(u32 val)            { m_localMaxHp = val; }
    inline void setCurrentMp(u32 val)             { m_currentMp = val; }
    inline void setMaxMp(u32 val)                 { m_maxMp = val; }
    inline void setLocalMaxMp(u32 val)            { m_localMaxMp = val; }
    inline void setBaseStr(u32 val)               { m_baseStr = val; }
    inline void setLocalStr(u32 val)              { m_localStr = val; }
    inline void setBaseDex(u32 val)               { m_baseDex = val; }
    inline void setLocalDex(u32 val)              { m_localDex = val; }
    inline void setBaseLuk(u32 val)               { m_baseLuk = val; }
    inline void setLocalLuk(u32 val)              { m_localLuk = val; }
    inline void setBaseInt(u32 val)               { m_baseInt = val; }
    inline void setLocalInt(u32 val)              { m_localInt = val; }
    inline void setMagic(u32 val)                 { m_magic = val; }
    inline void setWatk(u32 val)                  { m_watk = val; }
    inline void setSpeedModifier(float val)       { m_speedModifier = val; }
    inline void setJumpModifier(float val)        { m_jumpModifier = val; }
    inline void setGenderId(u32 val)              { m_genderId = val; }
    inline void setFaceId(u32 val)                { m_faceId = val; }
    inline void setHairId(u32 val)                { m_hairId = val; }
    inline void setSkinId(u32 val)                { m_skinId = val; }

private:
    u32              m_accountId     = 0;
    u32              m_characterId   = 0;
    u32              m_world         = 0;
    u32              m_channel       = 0;
    u32              m_mapId         = 0;
    u32              m_spawnpoint    = 0;
    std::string      m_characterName = "";
    u32              m_gmLevel       = 0;
    u32              m_job           = 0;
    u32              m_level         = 0;
    i32              m_rank          = 0;
    i32              m_rankMove      = 0;
    i32              m_jobRank       = 0;
    i32              m_jobRankMove   = 0;
    std::atomic<u32> m_exp           = 0;
    std::atomic<u32> m_mesos         = 0;
    i32              m_fame          = 0;
    u32              m_unspentAp     = 0;
    u32              m_unspentSp     = 0;
    u32              m_hpApUsed      = 0;
    u32              m_mpApUsed      = 0;
    u32              m_currentHp     = 0;
    u32              m_maxHp         = 0;
    u32              m_localMaxHp    = 0;
    u32              m_currentMp     = 0;
    u32              m_maxMp         = 0;
    u32              m_localMaxMp    = 0;
    u32              m_baseStr       = 0;
    u32              m_localStr      = 0;
    u32              m_baseDex       = 0;
    u32              m_localDex      = 0;
    u32              m_baseLuk       = 0;
    u32              m_localLuk      = 0;
    u32              m_baseInt       = 0;
    u32              m_localInt      = 0;
    u32              m_magic         = 0;
    u32              m_watk          = 0;
    float            m_speedModifier = 0;
    float            m_jumpModifier  = 0;
    u32              m_genderId      = 0;
    u32              m_faceId        = 0;
    u32              m_hairId        = 0;
    u32              m_skinId        = 0;

    // Misc
    //Map                    m_map;
    //Keymap                 m_keymap;
    //Buffs                  m_buffs;
    //Diseases               m_diseases;
    //Skills                 m_skills;
    std::map<u16, Inventory> m_inventory;
    //Storage                m_storage;
    //Quests                 m_quests;
    //Trade                  m_trade;
    //PlayerShop             m_shop;
    //BuddyList              m_buddyList;
    //Party                  m_party;
    //Guild                  m_guild;
    //Messenger              m_messenger;
};