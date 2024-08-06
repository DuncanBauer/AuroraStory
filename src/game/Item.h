#pragma once

#include "MapleConstants.h"
#include "Typedefs.h"

class Item
{
public:
    Item() :m_id(-1) {}
    Item(Item const& other)
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

    inline u32         const getItemType() const { return ItemType::k_ITEM; }

    // Getters
    inline u32         const getId()       const { return m_id; }
    inline std::string const getOwner()    const { return m_owner; }
    inline byte        const getPosition() const { return m_position; }
    inline u16         const getQuantity() const { return m_quantity; }
    inline u32         const getPetid()    const { return m_petId; }

    // Setters
    inline void              setId(u32 val)            { m_id = val; }
    inline void              setOwner(std::string val) { m_owner = val; }
    inline void              setPosition(byte val)     { m_position = val; }
    inline void              setQuantity(u32 val)      { m_quantity = val; }
    inline void              setPetId(u32 val)         { m_petId = val; }

private:
    u32         m_id       = 0;
    std::string m_owner    = "";
    byte        m_position = 0;
    u16         m_quantity = 0;
    u32         m_petId    = 0;
};

