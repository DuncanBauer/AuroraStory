#pragma once

#include "Item.h"
#include "constants/MapleConstants.h"
#include "Typedefs.h"
#include "util/LoggingTool.h"

class Inventory
{
public:
    Inventory() = default;
    Inventory(u32 type, u32 slotLimit) 
    { 
        m_type = type; 
        m_slotLimit = slotLimit; 
    }
    ~Inventory() {}

    void addItemFromDB(Item item);

    // Getters
    inline u32                            getInventoryType()        const { return m_type; }
    inline u32                            getSlotLimit()            const { return m_slotLimit; }
    inline std::unordered_map<byte, Item> getItems()                const { return m_items; }
           Item                           getItemInSlot(byte slot);

    // Setters

private:
    u32                            m_type      = 0;
    u32                            m_slotLimit = 0;
    std::unordered_map<byte, Item> m_items;
};