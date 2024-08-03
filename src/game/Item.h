#pragma once

#include "MapleConstants.h"
#include "Typedefs.h"

class Item
{
public:
    Item() { m_id = -1; };
    Item(const Item& other)
    {
        m_id = other.m_id;
        m_owner = other.m_owner;
        m_position = other.m_position;
        m_quantity = other.m_quantity;
        m_petId = other.m_petId;
    }
    Item(u32 id, byte position, u32 quantity) : m_id(id), m_position(position), m_quantity(quantity), m_petId(-1) {}
    Item(u32 id, byte position, u32 quantity, u32 petId) : m_id(id), m_position(position), m_quantity(quantity), m_petId(petId) {}
    ~Item() {}

    inline const u32 getItemType() const { return ItemType::k_ITEM; }

    // Getters
    inline const u32 getId() const { return m_id; }
    inline const std::string getOwner() const { return m_owner;}
    inline const byte getPosition() const { return m_position; }
    inline const u16 getQuantity() const { return m_quantity; }
    inline const u32 getPetid() const { return m_petId; }

    // Setters
    inline void setId(u32 val) { m_id = val; }
    inline void setOwner(std::string val) { m_owner = val; }
    inline void setPosition(byte val) { m_position = val; }
    inline void setQuantity(u32 val) { m_quantity = val; }
    inline void setPetId(u32 val) { m_petId = val; }

private:
    u32 m_id;
    std::string m_owner = "";
    byte m_position;
    u16 m_quantity;
    u32 m_petId;
};

