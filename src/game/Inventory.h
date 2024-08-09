#pragma once

#include "Item.h"
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

    // Getters
    inline u32                  getInventoryType()       const { return m_type; }
    inline u32                  getSlotLimit()           const { return m_slotLimit; }
    inline std::map<byte, Item> getItems()               const { return m_items; }
    inline Item                 getItemInSlot(byte slot)
    {
        Item item;
        try
        {
            item = m_items.at(slot);
        }
        catch (std::exception e)
        {
            SERVER_ERROR("Inventory::getItemInSlot: {}", e.what());
        }
        return item;
    }
    // Setters

private:
    u32                  m_type      = 0;
    u32                  m_slotLimit = 0;
    std::map<byte, Item> m_items;
};