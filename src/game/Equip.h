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
    inline const byte getUpgradeSlots() const { return m_upgradeSlots; }
    inline const byte getLocked() const { return m_locked; }
    inline const u32 getRingId() const { return m_ringId; }
    inline const byte getLevel() const { return m_level; }
    inline const u16 getJob() const { return m_job; }
    inline const u16 getHp() const { return m_hp; }
    inline const u16 getMp() const { return m_mp; }
    inline const u16 getStr() const { return m_str; }
    inline const u16 getDex() const { return m_dex; }
    inline const u16 getInt() const { return m_int; }
    inline const u16 getLuk() const { return m_luk; }
    inline const u16 getWatk() const { return m_watk; }
    inline const u16 getMatk() const { return m_matk; }
    inline const u16 getWdef() const { return m_wdef; }
    inline const u16 getMdef() const { return m_mdef; }
    inline const u16 getAcc() const { return m_acc; }
    inline const u16 getAvoid() const { return m_avoid; }
    inline const u16 getHands() const { return m_hands; }
    inline const u16 getSpeed() const { return m_speed; }
    inline const u16 getJump() const { return m_jump; }

    // Setters
    inline void setUpgradeSlots(byte val) { m_upgradeSlots = val; }
    inline void setLocked(byte val) { m_locked = val; }
    inline void setRingId(u32 val) { m_ringId = val; }
    inline void setLevel(byte val) { m_level = val; }
    inline void setJob(u16 val) { m_job = val; }
    inline void setHp(u16 val) { m_hp = val; }
    inline void setMp(u16 val) { m_mp = val; }
    inline void setStr(u16 val) { m_str = val; }
    inline void setDex(u16 val) { m_dex = val; }
    inline void setInt(u16 val) { m_int = val; }
    inline void setLuk(u16 val) { m_luk = val; }
    inline void setWatk(u16 val) { m_watk = val; }
    inline void setMatk(u16 val) { m_matk = val; }
    inline void setWdef(u16 val) { m_wdef = val; }
    inline void setMdef(u16 val) { m_mdef = val; }
    inline void setAcc(u16 val) { m_acc = val; }
    inline void setAvoid(u16 val) { m_avoid = val; }
    inline void setHands(u16 val) { m_hands = val; }
    inline void setSpeed(u16 val) { m_speed = val; }
    inline void setJump(u16 val) { m_jump = val; }

private:
    byte m_upgradeSlots;
    byte m_locked;
    u32 m_ringId;
    byte m_level;
    u16 m_job;
    u16 m_hp;
    u16 m_mp;
    u16 m_str;
    u16 m_dex;
    u16 m_int;
    u16 m_luk;
    u16 m_watk;
    u16 m_matk;
    u16 m_wdef;
    u16 m_mdef;
    u16 m_acc;
    u16 m_avoid;
    u16 m_hands;
    u16 m_speed;
    u16 m_jump;
};