#pragma once

#include "Typedefs.h"

class StatEffect
{
private:
    u16    m_watk;
    u16    m_matk;
    u16    m_wdef;
    u16    m_mdef;
    u16    m_acc;
    u16    m_avoid;
    u16    m_hands;
    u16    m_speed;
    u16    m_jump;
    u16    m_hp;
    u16    m_mp;
    double m_hpR;
    u16    m_mpR;
    u16    m_mpCon;
    u16    m_hpCon;
    u32    m_duration;
    bool   m_overTime;
    u32    m_sourceid;
    u32    m_moveTo;
    bool   m_skill;
    u32    m_x;
    u32    m_y;
    u32    m_z;
    double m_prop;
    u32    m_iProp;
    u32    m_itemCon;
    u32    m_itemConNo;
    u32    m_damage;
    u32    m_attackCount;
    u32    m_bulletCount;
    u32    m_bulletConsume;
    Point  m_lt;
    Point  m_rb;
    u32    m_mobCount;
    u32    m_moneyCon;
    u32    m_cooldown;
    bool   m_isMorph = false;
    u32    m_morphId = 0;
    u32    m_mastery;
    u32    m_range;
    //std::vector<std::pair<MapleBuffStat, u32>> m_statups;
    //std::unordered_map<MonsterStatus, u32>     m_monsterStatus;
    //std::vector<MapleDisease>                  m_cureDebuffs;
};

