#pragma once

#include "Item.h"
#include "Typedefs.h"

class Equip : public Item
{
public:
    Equip() = delete;
    Equip(u32 id, byte position) : Item(id, position, 1) {}
    Equip(u32 id, byte position, int ringId) : Item(id, position, 1), m_ringId(ringId) {}
    ~Equip() {}

    inline u32 getItemType() { return ItemType::k_EQUIP; }

    // Getters
    inline byte const getUpgradeSlots() const { return m_upgradeSlots; }
    inline byte const getLocked()       const { return m_locked; }
    inline u32  const getRingId()       const { return m_ringId; }
    inline byte const getLevel()        const { return m_level; }
    inline u16  const getJob()          const { return m_job; }
    inline u16  const getHp()           const { return m_hp; }
    inline u16  const getMp()           const { return m_mp; }
    inline u16  const getStr()          const { return m_str; }
    inline u16  const getDex()          const { return m_dex; }
    inline u16  const getInt()          const { return m_int; }
    inline u16  const getLuk()          const { return m_luk; }
    inline u16  const getWatk()         const { return m_watk; }
    inline u16  const getMatk()         const { return m_matk; }
    inline u16  const getWdef()         const { return m_wdef; }
    inline u16  const getMdef()         const { return m_mdef; }
    inline u16  const getAcc()          const { return m_acc; }
    inline u16  const getAvoid()        const { return m_avoid; }
    inline u16  const getHands()        const { return m_hands; }
    inline u16  const getSpeed()        const { return m_speed; }
    inline u16  const getJump()         const { return m_jump; }

    // Setters
    inline void setUpgradeSlots(byte val)     { m_upgradeSlots = val; }
    inline void setLocked(byte val)           { m_locked = val; }
    inline void setRingId(u32 val)            { m_ringId = val; }
    inline void setLevel(byte val)            { m_level = val; }
    inline void setJob(u16 val)               { m_job = val; }
    inline void setHp(u16 val)                { m_hp = val; }
    inline void setMp(u16 val)                { m_mp = val; }
    inline void setStr(u16 val)               { m_str = val; }
    inline void setDex(u16 val)               { m_dex = val; }
    inline void setInt(u16 val)               { m_int = val; }
    inline void setLuk(u16 val)               { m_luk = val; }
    inline void setWatk(u16 val)              { m_watk = val; }
    inline void setMatk(u16 val)              { m_matk = val; }
    inline void setWdef(u16 val)              { m_wdef = val; }
    inline void setMdef(u16 val)              { m_mdef = val; }
    inline void setAcc(u16 val)               { m_acc = val; }
    inline void setAvoid(u16 val)             { m_avoid = val; }
    inline void setHands(u16 val)             { m_hands = val; }
    inline void setSpeed(u16 val)             { m_speed = val; }
    inline void setJump(u16 val)              { m_jump = val; }

private:
    byte m_upgradeSlots = 0;
    byte m_locked       = 0;
    u32  m_ringId       = 0;
    byte m_level        = 0;
    u16  m_job          = 0;
    u16  m_hp           = 0;
    u16  m_mp           = 0;
    u16  m_str          = 0;
    u16  m_dex          = 0;
    u16  m_int          = 0;
    u16  m_luk          = 0;
    u16  m_watk         = 0;
    u16  m_matk         = 0;
    u16  m_wdef         = 0;
    u16  m_mdef         = 0;
    u16  m_acc          = 0;
    u16  m_avoid        = 0;
    u16  m_hands        = 0;
    u16  m_speed        = 0;
    u16  m_jump         = 0;
};