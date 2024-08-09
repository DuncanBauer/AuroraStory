#include <regex>
#include <unordered_set>

#include "Character.h"
#include "Master.h"
#include "Player.h"
#include "net/packets/PacketCreator.h"
#include "util/LoggingTool.h"
#include "util/MongoDb.h"

Character::Character()
{}

Character::Character(u32 const accountId, u32 const worldId)
{
    this->m_accountId = accountId;
    this->m_world = worldId;
}

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

bool Character::canCreateCharacter(std::string const& name, u32 world)
{
    // Check if its within legal length
    if (name.length() < 3 || name.length() > 12)
    {
        return false;
    }

    // Check to make sure it starts with a character and only contains letters and numbers
    std::regex pattern("[a-zA-Z0-9]{3,12}");
    if (!std::regex_match(name, pattern))
    {
        return false;
    }

    // Doesn't the regex already do this....?
    //// Check for symbols
    //std::vector<char> symbols = { '`','~','!','@','#','$','%','^',
    //                              '&','*','(', ')','_','-','=','+',
    //                              '{','[',']','}','|',';',':','\'',
    //                              ',','<','>','.','?','/' };

    //for (byte s = 0; s < symbols.size(); s++)
    //{
    //    if (name.find(symbols[s]) != std::string::npos)
    //    {
    //        return false;
    //    }
    //}

    // Check to make sure a character doesn't already exist with this name in this world
    return !Character::getCharacterIdByName(name, world);
}

u32 Character::createCharacter(std::shared_ptr<Player> player, std::string name, 
                               u32 face,    u32 hair,    u32 hairColor, u32 skin, 
                               u32 top,     u32 bottom,  u32 shoes,     u32 weapon, u32 gender, 
                               u32 baseStr, u32 baseDex, u32 baseInt,   u32 baseLuk)
{
    //characters(str, dex, luk, int, gm, skincolor, gender, job, hair, face, map,  meso, 
    //           spawnpoint, accountid, name, world, hp, mp, maxhp, maxmp, level, ap, sp)

    // Starting equip options
    std::unordered_set<u32> legalItems = { 1302000, 1312004, 1322005, 1442079,                                          // weapons
                                           1040002, 1040006, 1040010, 1041002, 1041006, 1041010, 1041011, 1042167,      // bottom
                                           1060002, 1060006, 1061002, 1061008, 1062115,                                 // top
                                           1072001, 1072005, 1072037, 1072038, 1072383,                                 // shoes
                                           30000, 30010,30020, 30030, 31000, 31040, 31050,                              // hair
                                           20000, 20001, 20002, 21000, 21001, 21002, 21201, 20401, 20402, 21700, 20100  // face
    };

    // Check to make sure all pieces of starting equipment are allowed by the server and not
    // packet edited
    std::vector<u32> items{ weapon, top, bottom, shoes, hair, face };
    for (size_t i = 0; i < items.size(); i++)
    {
        auto it = std::find(legalItems.begin(), legalItems.end(), items[i]);
        if (it == legalItems.end())
        {
            //FilePrinter.printError(FilePrinter.EXPLOITS + name + ".txt", "Owner from account '" + c.getAccountName() + "' tried to packet edit in char creation.");
            player->disconnect();
            return -1;
        }
    }

    // Check account has available character slots in this world
         
         
         
    // Check the character name is available in this world
    if (!canCreateCharacter(name, player->getWorld()))
    {
        return -1;
    }

    // Create the new character and add it to the DB
    Character newChar(player->getId(), player->getWorld());
    newChar.setCharacterName(name);
    newChar.setJob(Job::k_BEGINNER);
    newChar.setLevel(1);
    newChar.setGenderId(gender);
    newChar.setFaceId(face);
    newChar.setHairId(hair);
    newChar.setSkinId(skin);
    newChar.setMapId(10000); // This should be the starting map... I hope

    Inventory equipped = newChar.getInventory(InventoryType::k_EQUIPPED);
    //ItemInformationProvider ii = MapleItemInformationProvider.getInstance();

    //// Add starting equipment to the equipped inventory
    //if (top > 0) 
    //{
    //    Item eq_top = ii.getEquipById(top);
    //    eq_top.setPosition((byte)-5);
    //    equipped.addItemFromDB(eq_top);
    //}

    //if (bottom > 0) 
    //{
    //    Item eq_bottom = ii.getEquipById(bottom);
    //    eq_bottom.setPosition((byte)-6);
    //    equipped.addItemFromDB(eq_bottom);
    //}

    //if (shoes > 0) 
    //{
    //    Item eq_shoes = ii.getEquipById(shoes);
    //    eq_shoes.setPosition((byte)-7);
    //    equipped.addItemFromDB(eq_shoes);
    //}

    //if (weapon > 0) 
    //{
    //    Item eq_weapon = ii.getEquipById(weapon);
    //    eq_weapon.setPosition((byte)-11);
    //    equipped.addItemFromDB(eq_weapon.copy());
    //}

    //// Try to insert a new character into the DB
    //if (!newChar.insertNewChar(recipe))
    //{
    //    return -2;
    //}
    //
    //player->send(PacketCreator::addNewCharEntry(newChar));
    //Master::getInstance().createCharacterEntry(newChar);
    SERVER_INFO("{} created a new character: {}", player->getAccount().username, newChar.getCharacterName());
    return 0;
}

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

bool Character::saveToDB()
{
    return true;
}

Inventory& Character::getInventory(u32 const inventoryType)
{
    return m_inventory[inventoryType];
}