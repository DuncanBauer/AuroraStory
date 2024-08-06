#include "Character.h"
#include "util/MongoDb.h"

Character::Character()
{}

Character::Character(const Character& other)
{
    this->m_characterId   = other.m_characterId;
    this->m_characterName = other.m_characterName;
    this->m_world         = other.m_world;
    this->m_channel       = other.m_channel;
    this->m_mapId         = other.m_mapId;
    this->m_spawnpoint    = other.m_spawnpoint;
    this->m_job           = other.m_job;
    this->m_level         = other.m_level;
    this->m_rank          = other.m_rank;
    this->m_rankMove      = other.m_rankMove;
    this->m_jobRank       = other.m_jobRank;
    this->m_jobRankMove   = other.m_jobRankMove;
    this->m_exp.store(other.m_exp, std::memory_order_relaxed);
    this->m_mesos.store(other.m_mesos, std::memory_order_relaxed);
    this->m_fame          = other.m_fame;
    this->m_unspentAp     = other.m_unspentAp;
    this->m_unspentSp     = other.m_unspentSp;
    this->m_hpApUsed      = other.m_hpApUsed;
    this->m_mpApUsed      = other.m_mpApUsed;
    this->m_currentHp     = other.m_currentHp;
    this->m_maxHp         = other.m_maxHp;
    this->m_localMaxHp    = other.m_localMaxHp;
    this->m_currentMp     = other.m_currentMp;
    this->m_maxMp         = other.m_maxMp;
    this->m_localMaxMp    = other.m_localMaxMp;
    this->m_baseStr       = other.m_baseStr;
    this->m_localStr      = other.m_localStr;
    this->m_baseDex       = other.m_baseDex;
    this->m_localDex      = other.m_localDex;
    this->m_baseLuk       = other.m_baseLuk;
    this->m_localLuk      = other.m_localLuk;
    this->m_baseInt       = other.m_baseInt;
    this->m_localInt      = other.m_localInt;
    this->m_magic         = other.m_magic;
    this->m_watk          = other.m_watk;
    this->m_speedModifier = other.m_speedModifier;
    this->m_jumpModifier  = other.m_jumpModifier;
    this->m_genderId      = other.m_genderId;
    this->m_faceId        = other.m_faceId;
    this->m_hairId        = other.m_hairId;
    this->m_skinId        = other.m_skinId;

    // Inventory
    m_inventory.emplace(InventoryType::k_EQUIPPED,  Inventory(InventoryType::k_EQUIPPED, 100));
    m_inventory.emplace(InventoryType::k_UNDEFINED, Inventory(InventoryType::k_UNDEFINED, 100));
    m_inventory.emplace(InventoryType::k_EQUIP,     Inventory(InventoryType::k_EQUIP, 100));
    m_inventory.emplace(InventoryType::k_USE,       Inventory(InventoryType::k_USE, 100));
    m_inventory.emplace(InventoryType::k_SETUP,     Inventory(InventoryType::k_SETUP, 100));
    m_inventory.emplace(InventoryType::k_ETC,       Inventory(InventoryType::k_ETC, 100));
    m_inventory.emplace(InventoryType::k_CASH,      Inventory(InventoryType::k_CASH, 100));
}

Character::~Character()
{}

const u32 Character::getCharacterIdByName(std::string name, u16 world)
{
    FindOneResult result = util::MongoDb::getInstance().getCharacterByName(name, world);
    if (result)
    {
        return (u32)std::stoull((*result).view()["_id"].get_oid().value.to_string());
    }

    // Character not found
    return 0;
}

const std::string Character::getCharacterNameById(u32 id, u16 world)
{
    FindOneResult result = util::MongoDb::getInstance().getCharacterById(id, world);
    if (result)
    {
        return std::string((*result).view()["name"].get_string().value);
    }
    return "";
}

Inventory& Character::getInventory(u16 inventoryType)
{
    return m_inventory[inventoryType];
}