#pragma once

#include <string>

namespace Wz
{
    enum class WzMapleVersion
    {
        GMS,
        MSEA,
        BMS,
        EMS,
        JMS,
        KMS,
        CLASSIC, 
        GENERATE, 
        GETFROMZLZ
    };

    enum class WzObjectType
    {
        FILE,
        IMAGE,
        DIRECTORY,
        PROPERTY,
        LIST
    };

    enum class WzPropertyType
    {
        NULL_TYPE,
        SHORT, 
        INT, 
        LONG, 
        FLOAT,
        DOUBLE,
        STRING,
        
        SUBPROPERTY,
        CANVAS,
        VECTOR, 
        CONVEX, 
        SOUND, 
        UOL,
        
        PNG
    };

        // For later WZ editing - write now we just want to read/write
    //enum class WzItemTypes
    //{
    //    NONE = 0x0,
    //    TILES = 0x1,
    //    OBJECTS = 0x2,
    //    MOBS = 0x4,
    //    NPCS = 0x8,
    //    ROPES = 0x10,
    //    FOOTHOLDS = 0x20,
    //    PORTALS = 0x40,
    //    CHAIRS = 0x80,
    //    REACTORS = 0x100,
    //    TOOLTIPS = 0x200,
    //    BACKGROUNDS = 0x400,
    //    MISC = 0x800,
    //    ALL = 0xFFF
    //};

    //enum class FieldLimit
    //{
    //    FIELDOPT_NONE = 0,
    //    FIELDOPT_MOVELIMIT = 1,
    //    FIELDOPT_SKILLLIMIT = 2,
    //    FIELDOPT_SUMMONLIMIT = 4,
    //    FIELDOPT_MYSTICDOORLIMIT = 8,
    //    FIELDOPT_MIGRATELIMIT = 0x10,
    //    FIELDOPT_PORTALSCROLLLIMIT = 0x20,
    //    FIELDOPT_TELEPORTITEMLIMIT = 0x40,
    //    FIELDOPT_MINIGAMELIMIT = 0x80,
    //    FIELDOPT_SPECIFICPORTALSCROLLLIMIT = 0x100,
    //    FIELDOPT_TAMINGMOBLIMIT = 0x200,
    //    FIELDOPT_STATCHANGEITEMCONSUMELIMIT = 0x400,
    //    FIELDOPT_PARTYBOSSCHANGELIMIT = 0x800,
    //    FIELDOPT_NOMOBCAPACITYLIMIT = 0x1000,
    //    FIELDOPT_WEDDINGINVITATIONLIMIT = 0x2000,
    //    FIELDOPT_CASHWEATHERCONSUMELIMIT = 0x4000,
    //    FIELDOPT_NOPET = 0x8000,
    //    FIELDOPT_ANTIMACROLIMIT = 0x10000,
    //    FIELDOPT_FALLDOWNLIMIT = 0x20000,
    //    FIELDOPT_SUMMONNPCLIMIT = 0x40000,
    //    FIELDOPT_NOEXPDECREASE = 0x80000,
    //    FIELDOPT_NODAMAGEONFALLING = 0x100000,
    //    FIELDOPT_PARCELOPENLIMIT = 0x200000,
    //    FIELDOPT_DROPLIMIT = 0x400000
    //};

    //enum class FieldType
    //{
    //    FIELDTYPE_DEFAULT = 0,
    //    FIELDTYPE_SNOWBALL = 1,
    //    FIELDTYPE_CONTIMOVE = 2,
    //    FIELDTYPE_TOURNAMENT = 3,
    //    FIELDTYPE_COCONUT = 4,
    //    FIELDTYPE_OXQUIZ = 5,
    //    FIELDTYPE_PERSONALTIMELIMIT = 6,
    //    FIELDTYPE_WAITINGROOM = 7,
    //    FIELDTYPE_GUILDBOSS = 8,
    //    FIELDTYPE_LIMITEDVIEW = 9,
    //    FIELDTYPE_MONSTERCARNIVAL = 0xA,
    //    FIELDTYPE_MONSTERCARNIVALREVIVE = 0xB,
    //    FIELDTYPE_ZAKUM = 0xC,
    //    FIELDTYPE_ARIANTARENA = 0xD,
    //    FIELDTYPE_DOJANG = 0xE,
    //    FIELDTYPE_MONSTERCARNIVAL_S2 = 0xF,
    //    FIELDTYPE_MONSTERCARNIVALWAITINGROOM = 0x10,
    //    FIELDTYPE_COOKIEHOUSE = 0x11,
    //    FIELDTYPE_BALROG = 0x12,
    //    FIELDTYPE_BATTLEFIELD = 0x13,
    //    FIELDTYPE_SPACEGAGA = 0x14,
    //    FIELDTYPE_WITCHTOWER = 0x15,
    //    FIELDTYPE_ARANTUTORIAL = 0x16,
    //    FIELDTYPE_MASSACRE = 0x17,
    //    FIELDTYPE_MASSACRE_RESULT = 0x18,
    //    FIELDTYPE_PARTYRAID = 0x19,
    //    FIELDTYPE_PARTYRAID_BOSS = 0x1A,
    //    FIELDTYPE_PARTYRAID_RESULT = 0x1B,
    //    FIELDTYPE_NODRAGON = 0x1C,
    //    FIELDTYPE_DYNAMICFOOTHOLD = 0x1D,
    //    FIELDTYPE_ESCORT = 0x1E,
    //    FIELDTYPE_ESCORT_RESULT = 0x1F,
    //    FIELDTYPE_HUNTINGADBALLOON = 0x20,
    //    FIELDTYPE_CHAOSZAKUM = 0x21,
    //    FIELDTYPE_KILLCOUNT = 0x22,
    //    FIELDTYPE_WEDDING = 0x3C,
    //    FIELDTYPE_WEDDINGPHOTO = 0x3D,
    //    FIELDTYPE_FISHINGKING = 0x4A,
    //    FIELDTYPE_SHOWABATH = 0x51,
    //    FIELDTYPE_BEGINNERCAMP = 0x52,
    //    FIELDTYPE_SNOWMAN = 1000,
    //    FIELDTYPE_SHOWASPA = 1001,
    //    FIELDTYPE_HORNTAILPQ = 1013,
    //    FIELDTYPE_CRIMSONWOODPQ = 1014
    //};

    //class PortalType
    //{
    //public:
    //    const std::string PORTALTYPE_STARTPOINT = "sp";
    //    const std::string PORTALTYPE_INVISIBLE = "pi";
    //    const std::string PORTALTYPE_VISIBLE = "pv";
    //    const std::string PORTALTYPE_COLLISION = "pc";
    //    const std::string PORTALTYPE_CHANGABLE = "pg";
    //    const std::string PORTALTYPE_CHANGABLE_INVISIBLE = "pgi";
    //    const std::string PORTALTYPE_TOWNPORTAL_POINT = "tp";
    //    const std::string PORTALTYPE_SCRIPT = "ps";
    //    const std::string PORTALTYPE_SCRIPT_INVISIBLE = "psi";
    //    const std::string PORTALTYPE_COLLISION_SCRIPT = "pcs";
    //    const std::string PORTALTYPE_HIDDEN = "ph";
    //    const std::string PORTALTYPE_SCRIPT_HIDDEN = "psh";
    //    const std::string PORTALTYPE_COLLISION_VERTICAL_JUMP = "pcj";
    //    const std::string PORTALTYPE_COLLISION_CUSTOM_IMPACT = "pci";
    //    const std::string PORTALTYPE_COLLISION_UNKNOWN_PCIG = "pcig";
    //};

    //enum class MapType
    //{
    //    REGULAR_MAP,
    //    MAP_LOGIN,
    //    CASH_SHOP_PREVIEW
    //};

    //enum class BackgroundType
    //{
    //    REGULAR = 0,
    //    HORIZONTAL_TILING = 1,
    //    VERTICAL_TILING = 2,
    //    HV_TILING = 3,
    //    HORIZONTAL_MOVING = 4,
    //    VERTICAL_MOVING = 5,
    //    HORIZONTAL_MOVING_HV_TILING = 6,
    //    VERTICAL_MOVING_HV_TILING = 7
    //};
}