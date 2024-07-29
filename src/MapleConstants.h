#pragma once

#include <string>

#include "Typedefs.h"

typedef unsigned char byte;

constexpr std::size_t k_packetHandshakeServerLength = 13; // the size of the handshake packet
constexpr short k_gameVersion = 62; // major game version
constexpr short k_gameMinorVersion = 1; // minor game version, if 0, then the string is empty
constexpr byte k_gmsLocale = 8;

constexpr std::size_t k_ivBufferSize = 16;
constexpr std::size_t k_headerSize = 4;
const std::string k_gameFilePath = "C:/Nexon/Maplestory/";

namespace Job
{
    constexpr u16 k_BEGINNER = 0;
    constexpr u16 k_WARRIOR = 100;
    constexpr u16 k_FIGHTER = 110;
    constexpr u16 k_CRUSADER = 111;
    constexpr u16 k_HERO = 112;
    constexpr u16 k_PAGE = 120;
    constexpr u16 k_WHITE_KNIGHT = 121;
    constexpr u16 k_PALADIN = 122;
    constexpr u16 k_SPEARMAN = 130;
    constexpr u16 k_DRAGON_KNIGHT = 131;
    constexpr u16 k_DARK_KNIGHT = 132;
    constexpr u16 k_MAGICIAN = 200;
    constexpr u16 k_FP_WIZARD = 210;
    constexpr u16 k_FP_MAGE = 211;
    constexpr u16 k_FP_ARCHMAGE = 212;
    constexpr u16 k_IL_WIZARD = 220;
    constexpr u16 k_IL_MAGE = 221;
    constexpr u16 k_IL_ARCHMAGE = 222;
    constexpr u16 k_CLERIC = 230;
    constexpr u16 k_PRIEST = 231;
    constexpr u16 k_BISHOP = 232;
    constexpr u16 k_BOWMAN = 300;
    constexpr u16 k_HUNTER = 310;
    constexpr u16 k_RANGER = 311;
    constexpr u16 k_BOW_MASTER = 312;
    constexpr u16 k_CROSSBOWMAN = 320;
    constexpr u16 k_SNIPER = 321;
    constexpr u16 k_CROSSBOW_MASTER = 322;
    constexpr u16 k_THIEF = 400;
    constexpr u16 k_ASSASSIN = 410;
    constexpr u16 k_HERMIT = 411;
    constexpr u16 k_NIGHT_LORD = 412;
    constexpr u16 k_BANDIT = 420;
    constexpr u16 k_CHIEF_BANDIT = 421;
    constexpr u16 k_SHADOWER = 422;
    constexpr u16 k_PIRATE = 500;
    constexpr u16 k_BRAWLER = 510;
    constexpr u16 k_MARAUDER = 511;
    constexpr u16 k_BUCCANEER = 512;
    constexpr u16 k_GUNSLINGER = 520;
    constexpr u16 k_OUTLAW = 521;
    constexpr u16 k_CORSAIR = 522;
    constexpr u16 k_GM = 900;
    constexpr u16 k_SUPERGM = 910;
};

namespace SkinColorId
{
    constexpr u16 k_NORMAL = 0;
    constexpr u16 k_DARK = 1;
    constexpr u16 k_BLACK = 2;
    constexpr u16 k_PALE = 3;
    constexpr u16 k_BLUE = 4;
    constexpr u16 k_WHITE = 9;
};

namespace MapleInventoryTypeId
{
    constexpr u16 k_EQUIPPED = -1;
    constexpr u16 k_UNDEFINED = 0;
    constexpr u16 k_EQUIP = 1;
    constexpr u16 k_USE = 2;
    constexpr u16 k_SETUP = 3;
    constexpr u16 k_ETC = 4;
    constexpr u16 k_CASH = 5;
};

// Values are the respective weapons max damage multipliers
namespace MapleWeaponTypeDmgMultiplier
{
    constexpr float k_NONE = 0.0f;
    constexpr float k_BOW = 3.4f;
    constexpr float k_CLAW = 3.6f;
    constexpr float k_DAGGER = 4.0f;
    constexpr float k_CROSSBOW = 3.6f;
    constexpr float k_AXE_1H = 4.4f;
    constexpr float k_AXE_2H = 4.8f;
    constexpr float k_SWORD_1H = 4.0f;
    constexpr float k_SWORD_2H = 4.6f;
    constexpr float k_BLUNT_1h = 4.4f;
    constexpr float k_BLUNT_2H = 4.8f;
    constexpr float k_POLEARM = 5.0f;
    constexpr float k_SPEAR = 5.0f;
    constexpr float k_STAFF = 3.6f;
    constexpr float k_WAND = 3.6f;
    constexpr float k_KNUCKLE = 4.0f;
    constexpr float k_GUN = 5.0f;
};

constexpr u32 expTable[201] = {
    0, 15, 34, 57, 92, 135, 372, 560, 840, 1242, 1716, 2360, 3216, 4200, 5460, 7050, 8840,
    11040, 13716, 16680, 20216, 24402, 28980, 34320, 40512, 47216, 54900, 63666, 73080, 83720, 95700, 108480,
    122760, 138666, 155540, 174216, 194832, 216600, 240500, 266682, 294216, 324240, 356916, 391160, 428280, 468450,
    510420, 555680, 604416, 655200, 709716, 748608, 789631, 832902, 878545, 926689, 977471, 1031036, 1087536,
    1147032, 1209994, 1276301, 1346242, 1420016, 1497832, 1579913, 1666492, 1757815, 1854143, 1955750, 2062925,
    2175973, 2295216, 2420993, 2553663, 2693603, 2841212, 2996910, 3161140, 3334370, 3517093, 3709829, 3913127,
    4127566, 4353756, 4592341, 4844001, 5109452, 5389449, 5684790, 5996316, 6324914, 6671519, 7037118, 7422752,
    7829518, 8258575, 8711144, 9188514, 9692044, 10223168, 10783397, 11374327, 11997640, 12655110, 13348610,
    14080113, 14851703, 15665576, 16524049, 17429566, 18384706, 19392187, 20454878, 21575805, 22758159, 24005306,
    25320796, 26708375, 28171993, 29715818, 31344244, 33061908, 34873700, 36784778, 38800583, 40926854, 43169645,
    45535341, 48030677, 50662758, 53439077, 56367538, 59456479, 62714694, 66151459, 69776558, 73600313, 77633610,
    81887931, 86375389, 91108760, 96101520, 101367883, 106992842, 112782213, 118962678, 125481832, 132358236,
    139611467, 147262175, 155332142, 163844343, 172823012, 182293713, 192283408, 202820538, 213935103, 225658746,
    238024845, 251068606, 264827165, 279339639, 294647508, 310794191, 327825712, 345790561, 364739883, 384727628,
    405810702, 428049128, 451506220, 476248760, 502347192, 529875818, 558913012, 589541445, 621848316, 655925603,
    691870326, 729784819, 769777027, 811960808, 856456260, 903390063, 952895838, 1005114529, 1060194805,
    1118293480, 1179575962, 1244216724, 1312399800, 1384319309, 1460180007, 1540197871, 1624600714, 1713628833,
    1807535693, 1906558648, 2011069705, 2121276324
};

constexpr u32 petExpTable[30] = {
    0, 1, 3, 6, 14, 31, 60, 108, 181, 287, 434, 632, 891, 1224, 1642, 2161, 2793, 3557,
    4467, 5542, 6801, 8263, 9950, 11882, 14084, 16578, 19391, 22547, 26074, 30000
};

constexpr u32 mountExpTable[30] = {
    0, 6, 25, 50, 105, 134, 196, 254, 263, 315, 367, 430, 543, 587, 679, 725, 897, 1146,
    1394, 1701, 2247, 2543, 2898, 3156, 3313, 3584, 3923, 4150, 4305, 4550
};