#pragma once

#include "MapleConstants.h"
#include "Inventory.h"
#include "Typedefs.h"

class Character
{
public:
    Character();
    Character(const Character& other);
    ~Character();

    static const u32 getCharacterIdByName(std::string name, u16 world);
    static const std::string getCharacterNameById(u32 id, u16 world);

    // Getters
    inline const u32 getCharacterId() const { return m_characterId; }
    inline const std::string getCharacterName() const { return m_characterName; }
    inline const u16 getWorld() const { return m_world; }
    inline const u16 getChannel() const { return m_channel; }
    inline const u32 getMapId() const { return m_mapId; }
    inline const u32 getSpawnpoint() const { return m_spawnpoint; }
    inline const u16 getJob() const { return m_job; }
    inline const u16 getLevel() const { return m_level; }
    inline const i32 getRank() const { return m_rank; }
    inline const i32 getRankMove() const { return m_rankMove; }
    inline const i32 getJobRank() const { return m_jobRank; }
    inline const i32 getJobRankMove() const { return m_jobRankMove; }
    inline const u32 getExp() const { return m_exp.load(std::memory_order_relaxed); }
    inline const u32 getMesos() const { return m_mesos.load(std::memory_order_relaxed); }
    inline const i32 getFame() const { return m_fame; }
    inline const u32 getUnspentAp() const { return m_unspentAp; }
    inline const u32 getUnspentSp() const { return m_unspentSp; }
    inline const u32 getHpApUsed() const { return m_hpApUsed; }
    inline const u32 getMpApUsed() const { return m_mpApUsed; }
    inline const u32 getCurrentHp() const { return m_currentHp; }
    inline const u32 getMaxHp() const { return m_maxHp; }
    inline const u32 getLocalMaxHp() const { return m_localMaxHp; }
    inline const u32 getCurrentMp() const { return m_currentMp; }
    inline const u32 getMaxMp() const { return m_maxMp; }
    inline const u32 getLocalMaxMp() const { return m_localMaxMp; }
    inline const u32 getBaseStr() const { return m_baseStr; }
    inline const u32 getLocalStr() const { return m_localStr; }
    inline const u32 getBaseDex() const { return m_baseDex; }
    inline const u32 getLocalDex() const { return m_localDex; }
    inline const u32 getBaseLuk() const { return m_baseLuk; }
    inline const u32 getLocalLuk() const { return m_localLuk; }
    inline const u32 getBaseInt() const { return m_baseInt; }
    inline const u32 getLocalInt() const { return m_localInt; }
    inline const u32 getMagic() const { return m_magic; }
    inline const u32 getWatk() const { return m_watk; }
    inline const float getSpeedModifier() const { return m_speedModifier; }
    inline const float getJumpModifier() const { return m_jumpModifier; }
    inline const u32 getGenderId() const { return m_genderId; }
    inline const u32 getFaceId() const { return m_faceId; }
    inline const u32 getHairId() const { return m_hairId; }
    inline const u32 getSkinId() const { return m_skinId; }

    Inventory& getInventory(u16 inventoryType);

    // Setters
    inline void setCharacterId(u32 val) { m_characterId = val; }
    inline void setCharacterName(std::string val) { m_characterName = val; }
    inline void setWorld(u16 val) { m_world = val; }
    inline void setChannel(u16 val) { m_channel = val; }
    inline void setMapId(u32 val) { m_mapId = val; }
    inline void setSpawnpoint(u32 val) { m_spawnpoint = val; }
    inline void setJob(u16 val) { m_job = val; }
    inline void setLevel(u16 val) { m_level = val; }
    inline void setRank(i32 val) { m_rank = val; }
    inline void setRankMove(i32 val) { m_rankMove = val; }
    inline void setJobRank(i32 val) { m_jobRank = val; }
    inline void setJobRankMove(i32 val) { m_jobRankMove = val; }
    inline void setExp(u32 val) { m_exp.store(val, std::memory_order_relaxed); }
    inline void setMesos(u32 val) { m_mesos.store(val, std::memory_order_relaxed); }
    inline void setFame(i32 val) { m_fame = val; }
    inline void setUnspentAp(u32 val) { m_unspentAp = val; }
    inline void setUnspentSp(u32 val) { m_unspentSp = val; }
    inline void setHpApUsed(u32 val) { m_hpApUsed = val; }
    inline void setMpApUsed(u32 val) { m_mpApUsed = val; }
    inline void setCurrentHp(u32 val) { m_currentHp = val; }
    inline void setMaxHp(u32 val) { m_maxHp = val; }
    inline void setLocalMaxHp(u32 val) { m_localMaxHp = val; }
    inline void setCurrentMp(u32 val) { m_currentMp = val; }
    inline void setMaxMp(u32 val) { m_maxMp = val; }
    inline void setLocalMaxMp(u32 val) { m_localMaxMp = val; }
    inline void setBaseStr(u32 val) { m_baseStr = val; }
    inline void setLocalStr(u32 val) { m_localStr = val; }
    inline void setBaseDex(u32 val) { m_baseDex = val; }
    inline void setLocalDex(u32 val) { m_localDex = val; }
    inline void setBaseLuk(u32 val) { m_baseLuk = val; }
    inline void setLocalLuk(u32 val) { m_localLuk = val; }
    inline void setBaseInt(u32 val) { m_baseInt = val; }
    inline void setLocalInt(u32 val) { m_localInt = val; }
    inline void setMagic(u32 val) { m_magic = val; }
    inline void setWatk(u32 val) { m_watk = val; }
    inline void setSpeedModifier(float val) { m_speedModifier = val; }
    inline void setJumpModifier(float val) { m_jumpModifier = val; }
    inline void setGenderId(u32 val) { m_genderId = val; }
    inline void setFaceId(u32 val) { m_faceId = val; }
    inline void setHairId(u32 val) { m_hairId = val; }
    inline void setSkinId(u32 val) { m_skinId = val; }

private:
    u32 m_characterId;
    std::string m_characterName;
    u16 m_world;
    u16 m_channel;
    u32 m_mapId;
    u32 m_spawnpoint;

    u16 m_job;
    u16 m_level;
    i32 m_rank, m_rankMove;
    i32 m_jobRank, m_jobRankMove;

    std::atomic<u32> m_exp;
    std::atomic<u32> m_mesos;
    i32 m_fame;

    // Stats
    u32 m_unspentAp, m_unspentSp;
    u32 m_hpApUsed, m_mpApUsed;
    u32 m_currentHp, m_maxHp, m_localMaxHp;
    u32 m_currentMp, m_maxMp, m_localMaxMp;
    u32 m_baseStr, m_localStr;
    u32 m_baseDex, m_localDex;
    u32 m_baseLuk, m_localLuk;
    u32 m_baseInt, m_localInt;
    u32 m_magic, m_watk;
    float m_speedModifier, m_jumpModifier;

    // Appearance
    u32 m_genderId;
    u32 m_faceId;
    u32 m_hairId;
    u32 m_skinId;

    // Misc
    //Map m_map;
    //Keymap m_keymap;
    //Buffs m_buffs;
    //Diseases m_diseases;
    //Skills m_skills;
    std::map<u16, Inventory> m_inventory;
    //Storage m_storage;
    //Quests m_quests;
    //Trade m_trade;
    //PlayerShop m_shop;
    //BuddyList m_buddyList;
    //Party m_party;
    //Guild m_guild;
    //Messenger m_messenger;
};