#include "Inventory.h"

Item Inventory::getItemInSlot(byte slot)
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

void Inventory::addItemFromDB(Item item)
{
    if (item.getPosition() < 0 && m_type != Constants::InventoryType::k_EQUIPPED)
    {
        throw "Item with negative position in non-equipped IV wtf?";
    }

    m_items[item.getPosition()] = item;
}