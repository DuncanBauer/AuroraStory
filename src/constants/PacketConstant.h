#pragma once

#include <unordered_map>
#include <string>

namespace constant
{
    size_t maxPackets = 20; // Max numbers of packets to process at once

    namespace RecvOps
    {
        // GENERAL
        constexpr short k_PONG = 0x18;

        // LOGIN
        constexpr short k_LOGIN_PASSWORD = 0x01;
        constexpr short k_GUEST_LOGIN = 0x02;
        constexpr short k_SERVERLIST_REREQUEST = 0x04;
        constexpr short k_CHARLIST_REQUEST = 0x05;
        constexpr short k_SERVERSTATUS_REQUEST = 0x06;
        constexpr short k_SET_GENDER = 0x08;
        constexpr short k_AFTER_LOGIN = 0x09;
        constexpr short k_REGISTER_PIN = 0x0A;
        constexpr short k_SERVERLIST_REQUEST = 0x0B;
        constexpr short k_PLAYER_DC = 0xC0;
        constexpr short k_VIEW_ALL_CHAR = 0x0D;
        constexpr short k_PICK_ALL_CHAR = 0x0E;
        constexpr short k_CHAR_SELECT = 0x13;
        constexpr short k_CHECK_CHAR_NAME = 0x15;
        constexpr short k_CREATE_CHAR = 0x16;
        constexpr short k_DELETE_CHAR = 0x17;
        constexpr short k_CLIENT_START = 0x19;
        constexpr short k_RELOG = 0x1C;

        // CHANNEL
        constexpr short k_PLAYER_LOGGEDIN = 0x14;
        constexpr short k_STRANGE_DATA = 0x1A;
        constexpr short k_CHANGE_MAP = 0x23;
        constexpr short k_CHANGE_CHANNEL = 0x24;
        constexpr short k_ENTER_CASH_SHOP = 0x25;
        constexpr short k_MOVE_PLAYER = 0x26;
        constexpr short k_CANCEL_CHAIR = 0x27;
        constexpr short k_USE_CHAIR = 0x28;
        constexpr short k_CLOSE_RANGE_ATTACK = 0x29;
        constexpr short k_RANGED_ATTACK = 0x2A;
        constexpr short k_MAGIC_ATTACK = 0x2B;
        constexpr short k_ENERGY_ORB_ATTACK = 0x2C;
        constexpr short k_TAKE_DAMAGE = 0x2D;
        constexpr short k_GENERAL_CHAT = 0x2E;
        constexpr short k_CLOSE_CHALKBOARD = 0x2F;
        constexpr short k_FACE_EXPRESSION = 0x30;
        constexpr short k_USE_ITEMEFFECT = 0x31;
        constexpr short k_NPC_TALK = 0x36;
        constexpr short k_NPC_TALK_MORE = 0x38;
        constexpr short k_NPC_SHOP = 0x39;
        constexpr short k_STORAGE = 0x3A;
        constexpr short k_HIRED_MERCHANT_REQUEST = 0x3B;
        constexpr short k_DUEY_ACTION = 0x3D;
        constexpr short k_ITEM_SORT = 0x40;
        constexpr short k_ITEM_SORT2 = 0x41;
        constexpr short k_ITEM_MOVE = 0x42;
        constexpr short k_USE_ITEM = 0x43;
        constexpr short k_CANCEL_ITEM_EFFECT = 0x44;
        constexpr short k_USE_SUMMON_BAG = 0x46;
        constexpr short k_USE_MOUNT_FOOD = 0x48;
        constexpr short k_USE_CASH_ITEM = 0x49;
        constexpr short k_USE_CATCH_ITEM = 0x4A;
        constexpr short k_USE_SKILL_BOOK = 0x4B;
        constexpr short k_USE_RETURN_SCROLL = 0x4E;
        constexpr short k_USE_UPGRADE_SCROLL = 0x4F;
        constexpr short k_DISTRIBUTE_AP = 0x50;
        constexpr short k_HEAL_OVER_TIME = 0x51;
        constexpr short k_DISTRIBUTE_SP = 0x52;
        constexpr short k_SPECIAL_MOVE = 0x53;
        constexpr short k_CANCEL_BUFF = 0x54;
        constexpr short k_SKILL_EFFECT = 0x55;
        constexpr short k_MESO_DROP = 0x56;
        constexpr short k_GIVE_FAME = 0x57;
        constexpr short k_CHAR_INFO_REQUEST = 0x59;
        constexpr short k_CANCEL_DEBUFF = 0x5B;
        constexpr short k_CHANGE_MAP_SPECIAL = 0x5C;
        constexpr short k_USE_INNER_PORTAL = 0x5D;
        constexpr short k_VIP_ADD_MAP = 0x5E;
        constexpr short k_QUEST_ACTION = 0x62;
        constexpr short k_SKILL_MACRO = 0x65;
        constexpr short k_REPORT_PLAYER = 0x68;
        constexpr short k_PARTYCHAT = 0x6B;
        constexpr short k_WHISPER = 0x6C;
        constexpr short k_SPOUSE_CHAT = 0x6D;
        constexpr short k_MESSENGER = 0x6E;
        constexpr short k_PLAYER_SHOP = 0x6F;
        constexpr short k_PLAYER_INTERACTION = 0x6F;
        constexpr short k_PARTY_OPERATION = 0x70;
        constexpr short k_DENY_PARTY_REQUEST = 0x71;
        constexpr short k_GUILD_OPERATION = 0x72;
        constexpr short k_DENY_GUILD_REQUEST = 0x73;
        constexpr short k_BUDDYLIST_MODIFY = 0x76;
        constexpr short k_NOTE_ACTION = 0x77;
        constexpr short k_USE_DOOR = 0x79;
        constexpr short k_CHANGE_KEYMAP = 0x7B;
        constexpr short k_RING_ACTION = 0x7D;
        constexpr short k_ALLIANCE_OPERATION = 0x83;
        constexpr short k_BBS_OPERATION = 0x86;
        constexpr short k_ENTER_MTS = 0x87;
        constexpr short k_PET_TALK = 0x8B;
        constexpr short k_USE_SOLOMAN_ITEM = 0x89;
        constexpr short k_PET_AUTO_POT = 0x90;
        constexpr short k_MOVE_SUMMON = 0x94;
        constexpr short k_SUMMON_ATTACK = 0x95;
        constexpr short k_DAMAGE_SUMMON = 0x96;
        constexpr short k_MOVE_LIFE = 0x9D;
        constexpr short k_AUTO_AGGRO = 0x9E;
        constexpr short k_MOB_DAMAGE_MOB = 0xA1;
        constexpr short k_MONSTER_BOMB = 0xA2;
        constexpr short k_NPC_ACTION = 0xA6;
        constexpr short k_ITEM_PICKUP = 0xAB;
        constexpr short k_DAMAGE_REACTOR = 0xAE;
        constexpr short k_MONSTER_CARNIVAL = 0xB9;
        constexpr short k_PARTY_SEARCH_REGISTER = 0xBF;
        constexpr short k_PARTY_SEARCH_START = 0xBD;
        constexpr short k_PLAYER_UPDATE = 0xC0;
        constexpr short k_MAPLETV = 0xD4;
        constexpr short k_MTS_OP = 0xD9;

        // CASHSHOP
        constexpr short k_TOUCHING_CS = 0xC5;
        constexpr short k_BUY_CS_ITEM = 0xC6;
        constexpr short k_COUPON_CODE = 0xC7;

        // PET
        constexpr short k_SPAWN_PET = 0x5A;
        constexpr short k_MOVE_PET = 0x8C;
        constexpr short k_PET_CHAT = 0x8D;
        constexpr short k_PET_COMMAND = 0x8E;
        constexpr short k_PET_LOOT = 0x8F;
        constexpr short k_PET_FOOD = 0x47;
    }

    namespace SendOps
    {
        // GENERAL
        constexpr short k_PING = 0x11;

        // LOGIN
        constexpr short k_LOGIN_STATUS = 0x00;
        constexpr short k_SEND_LINK = 0x01;
        constexpr short k_SERVERSTATUS = 0x03;
        constexpr short k_GENDER_DONE = 0x04;
        constexpr short k_PIN_OPERATION = 0x06;
        constexpr short k_PIN_ASSIGNED = 0x07;
        constexpr short k_ALL_CHARLIST = 0x08;
        constexpr short k_SERVERLIST = 0x0A;
        constexpr short k_CHARLIST = 0x0B;
        constexpr short k_SERVER_IP = 0x0C;
        constexpr short k_CHAR_NAME_RESPONSE = 0x0D;
        constexpr short k_ADD_NEW_CHAR_ENTRY = 0x0E;
        constexpr short k_DELETE_CHAR_RESPONSE = 0x0F;
        constexpr short k_CHANNEL_SELECTED = 0x14;
        constexpr short k_RELOG_RESPONSE = 0x16;

        // CHANNEL
        constexpr short k_CHANGE_CHANNEL = 0x10;
        constexpr short k_MODIFY_INVENTORY_ITEM = 0x1A;
        constexpr short k_UPDATE_STATS = 0x1C;
        constexpr short k_GIVE_BUFF = 0x1D;
        constexpr short k_CANCEL_BUFF = 0x1E;
        constexpr short k_UPDATE_SKILLS = 0x21;
        constexpr short k_FAME_RESPONSE = 0x23;
        constexpr short k_SHOW_STATUS_INFO = 0x24;
        constexpr short k_SHOW_NOTES = 0x26;
        constexpr short k_UPDATE_VIPMAPLIST = 0x27;
        constexpr short k_UPDATE_MOUNT = 0x2D;
        constexpr short k_SHOW_QUEST_COMPLETION = 0x2E;
        constexpr short k_SEND_TITLE_BOX = 0x2F;
        constexpr short k_USE_SKILL_BOOK = 0x30;
        constexpr short k_FINISH_SORT = 0x31;
        constexpr short k_FINISH_SORT2 = 0x32;
        constexpr short k_REPORT_PLAYER = 0x33;
        constexpr short k_REPORTREPLY = 0x34;
        constexpr short k_BBS_OPERATION = 0x38;
        constexpr short k_CHAR_INFO = 0x3A;
        constexpr short k_PARTY_OPERATION = 0x3B;
        constexpr short k_BUDDYLIST = 0x3C;
        constexpr short k_GUILD_OPERATION = 0x3E;
        constexpr short k_ALLIANCE_OPERATION = 0x3F;
        constexpr short k_SPAWN_PORTAL = 0x40;
        constexpr short k_SERVERMESSAGE = 0x41;
        constexpr short k_YELLOW_TIP = 0x4A;
        constexpr short k_PLAYER_NPC = 0x4E;
        constexpr short k_MONSTER_BOOK = 0x4F;
        constexpr short k_AVATAR_MEGA = 0x54;
        constexpr short k_BLUE_POP_UP = 0x56;
        constexpr short k_BLUE_POP_UP2 = 0x57;
        constexpr short k_BLUE_POP_UP3 = 0x58;
        constexpr short k_GM_POLICE = 0x59;
        constexpr short k_SILVER_BOX_OPEN = 0x5A;
        constexpr short k_SKILL_MACRO = 0x5B;
        constexpr short k_WARP_TO_MAP = 0x5C;
        constexpr short k_MTS_OPEN = 0x5D;
        constexpr short k_CS_OPEN = 0x5E;
        constexpr short k_RESET_SCREEN = 0x60;
        constexpr short k_BLOCK_PORTAL = 0x61;
        constexpr short k_BLOCK_PORTAL_SHOP = 0x62;
        constexpr short k_SHOW_EQUIP_EFFECT = 0x63;
        constexpr short k_MULTICHAT = 0x64;
        constexpr short k_WHISPER = 0x65;
        constexpr short k_SPOUSE_CHAT = 0x66;
        constexpr short k_BOSS_ENV = 0x68;
        constexpr short k_MAP_EFFECT = 0x69;
        constexpr short k_GMEVENT_INSTRUCTIONS = 0x6D;
        constexpr short k_CLOCK = 0x6E;
        constexpr short k_BOAT_EFFECT = 0x6F;
        constexpr short k_BOAT_HIDE = 0x70;
        constexpr short k_ARIANT_SCOREBOARD = 0x76;
        constexpr short k_SPAWN_PLAYER = 0x78;
        constexpr short k_REMOVE_PLAYER_FROM_MAP = 0x79;
        constexpr short k_CHATTEXT = 0x7A;
        constexpr short k_CHALKBOARD = 0x7B;
        constexpr short k_UPDATE_CHAR_BOX = 0x7c;
        constexpr short k_SHOW_SCROLL_EFFECT = 0x7E;
        constexpr short k_SPAWN_PET = 0x7F;
        constexpr short k_MOVE_PET = 0x81;
        //constexpr short k_PET_CHAT = MOVE_PET 1;
        //constexpr short k_PET_NAMECHANGE = MOVE_PET 2;
        //constexpr short k_PET_COMMAND = MOVE_PET 4;
        constexpr short k_SPAWN_SPECIAL_MAPOBJECT = 0x86;
        constexpr short k_REMOVE_SPECIAL_MAPOBJECT = 0x87;
        constexpr short k_MOVE_SUMMON = 0x88;
        constexpr short k_SUMMON_ATTACK = 0x89;
        constexpr short k_DAMAGE_SUMMON = 0x8A;
        constexpr short k_SUMMON_SKILL = 0x8B;
        constexpr short k_MOVE_PLAYER = 0x8D;
        constexpr short k_CLOSE_RANGE_ATTACK = 0x8E;
        constexpr short k_RANGED_ATTACK = 0x8F;
        constexpr short k_MAGIC_ATTACK = 0x90;
        constexpr short k_SKILL_EFFECT = 0x92;
        constexpr short k_CANCEL_SKILL_EFFECT = 0x93;
        constexpr short k_DAMAGE_PLAYER = 0x94;
        constexpr short k_FACIAL_EXPRESSION = 0x95;
        constexpr short k_SHOW_ITEM_EFFECT = 0x96;
        constexpr short k_SHOW_CHAIR = 0x97;
        constexpr short k_UPDATE_CHAR_LOOK = 0x98;
        constexpr short k_SHOW_FOREIGN_EFFECT = 0x99;
        constexpr short k_GIVE_FOREIGN_BUFF = 0x9A;
        constexpr short k_CANCEL_FOREIGN_BUFF = 0x9B;
        constexpr short k_UPDATE_PARTYMEMBER_HP = 0x9C;
        constexpr short k_CANCEL_CHAIR = 0xA0;
        constexpr short k_SHOW_ITEM_GAIN_INCHAT = 0xA1;
        constexpr short k_LUCKSACK_PASS = 0xA4;
        constexpr short k_LUCKSACK_FAIL = 0xA5;
        constexpr short k_UPDATE_QUEST_INFO = 0xA6;
        constexpr short k_PLAYER_HINT = 0xA9;
        constexpr short k_COOLDOWN = 0xAD;
        constexpr short k_SPAWN_MONSTER = 0xAF;
        constexpr short k_KILL_MONSTER = 0xB0;
        constexpr short k_SPAWN_MONSTER_CONTROL = 0xB1;
        constexpr short k_MOVE_MONSTER = 0xB2;
        constexpr short k_MOVE_MONSTER_RESPONSE = 0xB3;
        constexpr short k_DAMAGE_MONSTER = 0xB9;
        constexpr short k_APPLY_MONSTER_STATUS = 0xB5;
        constexpr short k_CANCEL_MONSTER_STATUS = 0xB6;
        constexpr short k_MOB_TO_MOB_DAMAGE = 0xB8;
        constexpr short k_ARIANT_THING = 0xBC;
        constexpr short k_SHOW_MONSTER_HP = 0xBD;
        constexpr short k_SHOW_MAGNET = 0xBE;
        constexpr short k_CATCH_MONSTER = 0xBF;
        constexpr short k_SPAWN_NPC = 0xC2;
        constexpr short k_NPC_CONFIRM = 0xC3;
        constexpr short k_SPAWN_NPC_REQUEST_CONTROLLER = 0xC4;
        constexpr short k_NPC_ACTION = 0xC5;
        constexpr short k_SPAWN_HIRED_MERCHANT = 0xCA;
        constexpr short k_DESTROY_HIRED_MERCHANT = 0xCB;
        constexpr short k_UPDATE_HIRED_MERCHANT = 0xCC;
        constexpr short k_DROP_ITEM_FROM_MAPOBJECT = 0xCD;
        constexpr short k_REMOVE_ITEM_FROM_MAP = 0xCE;
        constexpr short k_SPAWN_MIST = 0xD2;
        constexpr short k_REMOVE_MIST = 0xD3;
        constexpr short k_SPAWN_DOOR = 0xD4;
        constexpr short k_REMOVE_DOOR = 0xD5;
        constexpr short k_REACTOR_HIT = 0xD6;
        constexpr short k_REACTOR_SPAWN = 0xD8;
        constexpr short k_REACTOR_DESTROY = 0xD9;
        constexpr short k_MONSTER_CARNIVAL_START = 0xE2;
        constexpr short k_MONSTER_CARNIVAL_OBTAINED_CP = 0xE3;
        constexpr short k_MONSTER_CARNIVAL_PARTY_CP = 0xE4;
        constexpr short k_MONSTER_CARNIVAL_SUMMON = 0xE5;
        constexpr short k_MONSTER_CARNIVAL_DIED = 0xE7;
        constexpr short k_ARIANT_PQ_START = 0xEA;
        constexpr short k_ZAKUM_SHRINE = 0xEC;
        constexpr short k_NPC_TALK = 0xED;
        constexpr short k_OPEN_NPC_SHOP = 0xEE;
        constexpr short k_CONFIRM_SHOP_TRANSACTION = 0xEF;
        constexpr short k_OPEN_STORAGE = 0xF0;
        constexpr short k_MESSENGER = 0xF4;
        constexpr short k_PLAYER_INTERACTION = 0xF5;
        constexpr short k_DUEY = 0xFD;
        constexpr short k_CS_UPDATE = 0xFF;
        constexpr short k_CS_OPERATION = 0x100;
        constexpr short k_KEYMAP = 0x107;
        constexpr short k_KITE = 0x10C;
        constexpr short k_SEND_TV = 0x10D;
        constexpr short k_REMOVE_TV = 0x10E;
        constexpr short k_ENABLE_TV = 0x10F;
        constexpr short k_MTS_OPERATION = 0x114;
        constexpr short k_MTS_OPERATION2 = 0x113;
    }
}