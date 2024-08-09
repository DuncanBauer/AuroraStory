#pragma once

#include <unordered_map>

#include "Master.h"
#include "client/Equip.h"
#include "client/StatEffect.h"
#include "provider/wz/WzDataProvider.h"

namespace Provider
{
    class ItemInfoProvider
    {
    public:
        static ItemInfoProvider& getInstance();

        Item getEquipById(u32 equipId);
        Item getEquipById(u32 equipId, u32 ringId);

        Provider::NxNode                     getItemData(u32 itemId);
        std::unordered_map<std::string, u32> getEquipStats(u32 itemId);

    private:
        /** Creates a new instance of MapleItemInformationProvider */
        ItemInfoProvider();

    private:
        std::shared_ptr<WzDataProvider> m_itemData;
        std::shared_ptr<WzDataProvider> m_equipData;
        std::shared_ptr<WzDataProvider> m_stringData;

        NxNode m_cashStringData;
        NxNode m_consumeStringData;
        NxNode m_eqpStringData;
        NxNode m_etcStringData;
        NxNode m_insStringData;
        NxNode m_petStringData;

        std::unordered_map<u32, u16>                                  m_inventoryTypeCache;
        std::unordered_map<u32, u16>                                  m_slotMaxCache;
        std::unordered_map<u32, StatEffect>                           m_itemEffects;
        std::unordered_map<u32, std::unordered_map<std::string, u32>> m_equipStatsCache;
        std::unordered_map<u32, Equip>                                m_equipCache;
        std::unordered_map<u32, double>                               m_priceCache;
        std::unordered_map<u32, u32>                                  m_wholePriceCache;
        std::unordered_map<u32, u32>                                  m_projectileWatkCache;
        std::unordered_map<u32, std::string>                          m_nameCache;
        std::unordered_map<u32, std::string>                          m_descCache;
        std::unordered_map<u32, std::string>                          m_msgCache;
        std::unordered_map<u32, bool>                                 m_dropRestrictionCache;
        std::unordered_map<u32, bool>                                 m_pickupRestrictionCache;
        std::vector<std::pair<u32, std::string>>                      m_itemNameCache;
        std::unordered_map<u32, u32>                                  m_getMesoCache;
        std::unordered_map<u32, u32>                                  m_getExpCache;
    };
}