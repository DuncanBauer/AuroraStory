#include "ItemInfoProvider.h"

namespace Provider
{
    ItemInfoProvider::ItemInfoProvider()
    {
        m_itemData   = Master::getInstance().getProviders()["Item"];
        m_equipData  = Master::getInstance().getProviders()["Character"];
        m_stringData = Master::getInstance().getProviders()["String"];

        m_cashStringData    = m_stringData->getData("Cash.img");
        m_consumeStringData = m_stringData->getData("Consume.img");
        m_eqpStringData     = m_stringData->getData("Eqp.img");
        m_etcStringData     = m_stringData->getData("Etc.img");
        m_insStringData     = m_stringData->getData("Ins.img");
        m_petStringData     = m_stringData->getData("Pet.img");
    }

    ItemInfoProvider& ItemInfoProvider::getInstance()
    {
        static ItemInfoProvider instance;
        return instance;
    }

    Item ItemInfoProvider::getEquipById(u32 equipId)
    {
        return getEquipById(equipId, -1);
    }

    Item ItemInfoProvider::getEquipById(u32 equipId, u32 ringId)
    {
        Equip equip(equipId, (byte)0, ringId);
        equip.setQuantity((u16)1);

        std::unordered_map<std::string, u32> stats = getEquipStats(equipId);
        if (!stats.empty()) 
        {
            auto it = stats.begin();
            while (it != stats.end())
            {
                std::string key = (*it).first;
                u32 value       = (*it).second;
                if (key == "STR")
                {
                    equip.setStr((u16)value);
                }
                else if (key == "DEX")
                {
                    equip.setDex((u16)value);
                }
                else if (key == "INT")
                {
                    equip.setInt((u16)value);
                }
                else if (key == "LUK")
                {
                    equip.setLuk((u16)value);
                }
                else if (key == "PAD")
                {
                    equip.setWatk((u16)value);
                }
                else if (key == "PDD")
                {
                    equip.setWdef((u16)value);
                }
                else if (key == "MAD")
                {
                    equip.setMatk((u16)value);
                }
                else if (key == "MDD")
                {
                    equip.setMdef((u16)value);
                }
                else if (key == "ACC")
                {
                    equip.setAcc((u16)value);
                }
                else if (key == "EVA")
                {
                    equip.setAvoid((u16)value);
                }
                else if (key == "Speed")
                {
                    equip.setSpeed((u16)value);
                }
                else if (key == "Jump")
                {
                    equip.setJump((u16)value);
                }
                else if (key == "MHP")
                {
                    equip.setHp((u16)value);
                }
                else if (key == "MMP")
                {
                    equip.setMp((u16)value);
                }
                else if (key == "tuc")
                {
                    equip.setUpgradeSlots((byte)value);
                }
                else if (key == "afterImage")
                {
                }
                it++;
            }
        }

        m_equipCache.emplace(equipId, equip);
        return equip;
    }

    NxNode ItemInfoProvider::getItemData(u32 itemId)
    {
        NxNode      ret;
        std::string idStr = "0" + std::to_string(itemId);
        NxNode      root  = m_itemData->getRoot();

        auto it = root.begin();
        while(it != root.end())
        {
            // we should have .img files here beginning with the first 4 IID
            auto childIt = it.begin();
            while(childIt != it.end())
            {
                if (childIt.getName() == idStr.substr(0, 4) + ".img")
                {
                    return m_itemData->getData(it.getName() + "/" + childIt.getName());
                }
                else if (childIt.getName() == idStr.substr(1) + ".img")
                {
                    return m_itemData->getData(it.getName() + "/" + childIt.getName());
                }
            }
        }

        root = m_equipData->getRoot();
        it   = root.begin();
        while (it != root.end())
        {
            // we should have .img files here beginning with the first 4 IID
            auto childIt = it.begin();
            while (childIt != it.end())
            {
                if (childIt.getName() == idStr + ".img")
                {
                    return m_equipData->getData(it.getName() + "/" + childIt.getName());
                }
            }
        }

        return ret;
    }

    std::unordered_map<std::string, u32> ItemInfoProvider::getEquipStats(u32 itemId)
    {
        if (m_equipStatsCache.find(itemId) != m_equipStatsCache.end())
        {
            return m_equipStatsCache[itemId];
        }
        
        std::unordered_map<std::string, u32> ret;
        NxNode item = getItemData(itemId);
        NxNode info = item.operator[]("info");
        
        auto it = info.begin();
        while (it != info.end())
        {
            if (it.getName().starts_with("inc"))
            {
                ret[it.getName().substr(3)] = (u32)it.getInt();
            }
        }

        ret["tuc"]      = (u32)info["tuc"].getInt();
        ret["reqLevel"] = (u32)info["reqLevel"].getInt();
        ret["cursed"]   = (u32)info["cursed"].getInt();
        ret["success"]  = (u32)info["success"].getInt();

        m_equipStatsCache[itemId] = ret;
        return ret;
    }
}