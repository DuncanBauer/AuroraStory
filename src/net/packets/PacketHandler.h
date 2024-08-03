#pragma once

#include <memory>


#include "net/packets/PacketConstants.h"
#include "net/asio/TCPConnection.h"
#include "game/Player.h"
#include "Typedefs.h"

using PacketHandlers = std::unordered_map<u32, std::function<void(std::shared_ptr<Player>, Packet&)>>;

enum ServerMode
{
    LOGIN,
    CHANNEL
};

class PacketHandler
{
public:
    PacketHandler() = delete;

    static inline void initialize()
    {
        // GENERAL
        m_packetHandlers[RecvOps::k_PONG]                    = [](std::shared_ptr<Player> player, Packet& packet) { handlePong(player, packet); };

        // LOGIN
        m_packetHandlers[RecvOps::k_LOGIN_PASSWORD]          = [](std::shared_ptr<Player> player, Packet& packet) { handleLoginPassword(player, packet); };
        m_packetHandlers[RecvOps::k_GUEST_LOGIN]             = [](std::shared_ptr<Player> player, Packet& packet) { handleGuestLogin(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_LIST_REREQUEST]   = [](std::shared_ptr<Player> player, Packet& packet) { handleServerListRerequest(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_LIST_REQUEST]       = [](std::shared_ptr<Player> player, Packet& packet) { handleCharacterListRequest(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_STATUS_REQUEST]   = [](std::shared_ptr<Player> player, Packet& packet) { handleServerStatusRequest(player, packet); };
        m_packetHandlers[RecvOps::k_SET_GENDER]              = [](std::shared_ptr<Player> player, Packet& packet) { handleSetGender(player, packet); };
        m_packetHandlers[RecvOps::k_AFTER_LOGIN]             = [](std::shared_ptr<Player> player, Packet& packet) { handleAfterLogin(player, packet); };
        m_packetHandlers[RecvOps::k_REGISTER_PIN]            = [](std::shared_ptr<Player> player, Packet& packet) { handleRegisterPin(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_LIST_REQUEST]     = [](std::shared_ptr<Player> player, Packet& packet) { handleServerListRequest(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_DC]               = [](std::shared_ptr<Player> player, Packet& packet) { handlePlayerDC(player, packet); };
        m_packetHandlers[RecvOps::k_VIEW_ALL_CHAR]           = [](std::shared_ptr<Player> player, Packet& packet) { handleViewAllChar(player, packet); };
        m_packetHandlers[RecvOps::k_PICK_ALL_CHAR]           = [](std::shared_ptr<Player> player, Packet& packet) { handlePickAllChar(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_SELECT]             = [](std::shared_ptr<Player> player, Packet& packet) { handleCharSelect(player, packet); };
        m_packetHandlers[RecvOps::k_CHECK_CHAR_NAME]         = [](std::shared_ptr<Player> player, Packet& packet) { handleCheckCharacterName(player, packet); };
        m_packetHandlers[RecvOps::k_CREATE_CHAR]             = [](std::shared_ptr<Player> player, Packet& packet) { handleCreateChar(player, packet); };
        m_packetHandlers[RecvOps::k_DELETE_CHAR]             = [](std::shared_ptr<Player> player, Packet& packet) { handleDeleteChar(player, packet); };
        m_packetHandlers[RecvOps::k_CLIENT_START]            = [](std::shared_ptr<Player> player, Packet& packet) { handleClientStart(player, packet); };
        m_packetHandlers[RecvOps::k_RELOG]                   = [](std::shared_ptr<Player> player, Packet& packet) { handleRelog(player, packet); };
         
        // CHANNEL
        m_packetHandlers[RecvOps::k_PLAYER_LOGGED_IN]        = [](std::shared_ptr<Player> player, Packet& packet) { handlePlayerLoggedIn(player, packet); };
        m_packetHandlers[RecvOps::k_STRANGE_DATA]            = [](std::shared_ptr<Player> player, Packet& packet) { handleStrangeData(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_MAP]              = [](std::shared_ptr<Player> player, Packet& packet) { handleChangeMap(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_CHANNEL]          = [](std::shared_ptr<Player> player, Packet& packet) { handleChangeChannel(player, packet); };
        m_packetHandlers[RecvOps::k_ENTER_CASH_SHOP]         = [](std::shared_ptr<Player> player, Packet& packet) { handleEnterCashShop(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_PLAYER]             = [](std::shared_ptr<Player> player, Packet& packet) { handleMovePlayer(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_CHAIR]            = [](std::shared_ptr<Player> player, Packet& packet) { handleCancelChair(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CHAIR]               = [](std::shared_ptr<Player> player, Packet& packet) { handleUseChair(player, packet); };
        m_packetHandlers[RecvOps::k_CLOSE_RANGE_ATTACK]      = [](std::shared_ptr<Player> player, Packet& packet) { handleCloseRangeAttack(player, packet); };
        m_packetHandlers[RecvOps::k_RANGED_ATTACK]           = [](std::shared_ptr<Player> player, Packet& packet) { handleRangedAttack(player, packet); };
        m_packetHandlers[RecvOps::k_MAGIC_ATTACK]            = [](std::shared_ptr<Player> player, Packet& packet) { handleMagicAttack(player, packet); };
        m_packetHandlers[RecvOps::k_ENERGY_ORB_ATTACK]       = [](std::shared_ptr<Player> player, Packet& packet) { handleEnergyOrbAttack(player, packet); };
        m_packetHandlers[RecvOps::k_TAKE_DAMAGE]             = [](std::shared_ptr<Player> player, Packet& packet) { handleTakeDamage(player, packet); };
        m_packetHandlers[RecvOps::k_GENERAL_CHAT]            = [](std::shared_ptr<Player> player, Packet& packet) { handleGeneralChat(player, packet); };
        m_packetHandlers[RecvOps::k_CLOSE_CHALKBOARD]        = [](std::shared_ptr<Player> player, Packet& packet) { handleCloseChalkboard(player, packet); };
        m_packetHandlers[RecvOps::k_FACE_EXPRESSION]         = [](std::shared_ptr<Player> player, Packet& packet) { handleFaceExpression(player, packet); };
        m_packetHandlers[RecvOps::k_USE_ITEM_EFFECT]         = [](std::shared_ptr<Player> player, Packet& packet) { handleUseItemEffect(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_TALK]                = [](std::shared_ptr<Player> player, Packet& packet) { handleNpcTalk(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_TALK_MORE]           = [](std::shared_ptr<Player> player, Packet& packet) { handleNpcTalkMore(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_SHOP]                = [](std::shared_ptr<Player> player, Packet& packet) { handleNpcShop(player, packet); };
        m_packetHandlers[RecvOps::k_STORAGE]                 = [](std::shared_ptr<Player> player, Packet& packet) { handleStorage(player, packet); };
        m_packetHandlers[RecvOps::k_HIRED_MERCHANT_REQUEST]  = [](std::shared_ptr<Player> player, Packet& packet) { handleHiredMerchantRequest(player, packet); };
        m_packetHandlers[RecvOps::k_DUEY_ACTION]             = [](std::shared_ptr<Player> player, Packet& packet) { handleDueyAction(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_SORT]               = [](std::shared_ptr<Player> player, Packet& packet) { handleItemSort(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_SORT2]              = [](std::shared_ptr<Player> player, Packet& packet) { handleItemSort2(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_MOVE]               = [](std::shared_ptr<Player> player, Packet& packet) { handleItemMove(player, packet); };
        m_packetHandlers[RecvOps::k_USE_ITEM]                = [](std::shared_ptr<Player> player, Packet& packet) { handleUseItem(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_ITEM_EFFECT]      = [](std::shared_ptr<Player> player, Packet& packet) { handleCancelItemEffect(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SUMMON_BAG]          = [](std::shared_ptr<Player> player, Packet& packet) { handleUseSummonBag(player, packet); };
        m_packetHandlers[RecvOps::k_USE_MOUNT_FOOD]          = [](std::shared_ptr<Player> player, Packet& packet) { handleUseMountFood(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CASH_ITEM]           = [](std::shared_ptr<Player> player, Packet& packet) { handleUseCashItem(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CATCH_ITEM]          = [](std::shared_ptr<Player> player, Packet& packet) { handleUseCatchItem(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SKILL_BOOK]          = [](std::shared_ptr<Player> player, Packet& packet) { handleUseSkillBook(player, packet); };
        m_packetHandlers[RecvOps::k_USE_RETURN_SCROLL]       = [](std::shared_ptr<Player> player, Packet& packet) { handleUseReturnScroll(player, packet); };
        m_packetHandlers[RecvOps::k_USE_UPGRADE_SCROLL]      = [](std::shared_ptr<Player> player, Packet& packet) { handleUseUpgradeScroll(player, packet); };
        m_packetHandlers[RecvOps::k_DISTRIBUTE_AP]           = [](std::shared_ptr<Player> player, Packet& packet) { handleDistributeAP(player, packet); };
        m_packetHandlers[RecvOps::k_HEAL_OVER_TIME]          = [](std::shared_ptr<Player> player, Packet& packet) { handleHealOverTime(player, packet); };
        m_packetHandlers[RecvOps::k_DISTRIBUTE_SP]           = [](std::shared_ptr<Player> player, Packet& packet) { handleDistributeSP(player, packet); };
        m_packetHandlers[RecvOps::k_SPECIAL_MOVE]            = [](std::shared_ptr<Player> player, Packet& packet) { handleSpecialMove(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_BUFF]             = [](std::shared_ptr<Player> player, Packet& packet) { handleCancelBuff(player, packet); };
        m_packetHandlers[RecvOps::k_SKILL_EFFECT]            = [](std::shared_ptr<Player> player, Packet& packet) { handleSkillEffect(player, packet); };
        m_packetHandlers[RecvOps::k_MESO_DROP]               = [](std::shared_ptr<Player> player, Packet& packet) { handleMesoDrop(player, packet); };
        m_packetHandlers[RecvOps::k_GIVE_FAME]               = [](std::shared_ptr<Player> player, Packet& packet) { handleGiveFame(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_INFO_REQUEST]       = [](std::shared_ptr<Player> player, Packet& packet) { handleCharInfoRequest(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_DEBUFF]           = [](std::shared_ptr<Player> player, Packet& packet) { handleCancelDebuff(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_MAP_SPECIAL]      = [](std::shared_ptr<Player> player, Packet& packet) { handleChangeMapSpecial(player, packet); };
        m_packetHandlers[RecvOps::k_USE_INNER_PORTAL]        = [](std::shared_ptr<Player> player, Packet& packet) { handleUseInnerPortal(player, packet); };
        m_packetHandlers[RecvOps::k_VIP_ADD_MAP]             = [](std::shared_ptr<Player> player, Packet& packet) { handleVipAddMap(player, packet); };
        m_packetHandlers[RecvOps::k_QUEST_ACTION]            = [](std::shared_ptr<Player> player, Packet& packet) { handleQuestAction(player, packet); };
        m_packetHandlers[RecvOps::k_SKILL_MACRO]             = [](std::shared_ptr<Player> player, Packet& packet) { handleSkillMacro(player, packet); };
        m_packetHandlers[RecvOps::k_REPORT_PLAYER]           = [](std::shared_ptr<Player> player, Packet& packet) { handleReportPlayer(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_CHAT]              = [](std::shared_ptr<Player> player, Packet& packet) { handlePartyChat(player, packet); };
        m_packetHandlers[RecvOps::k_WHISPER]                 = [](std::shared_ptr<Player> player, Packet& packet) { handleWhisper(player, packet); };
        m_packetHandlers[RecvOps::k_SPOUSE_CHAT]             = [](std::shared_ptr<Player> player, Packet& packet) { handleSpouseChat(player, packet); };
        m_packetHandlers[RecvOps::k_MESSENGER]               = [](std::shared_ptr<Player> player, Packet& packet) { handleMessenger(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_SHOP]             = [](std::shared_ptr<Player> player, Packet& packet) { handlePlayerShop(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_INTERACTION]      = [](std::shared_ptr<Player> player, Packet& packet) { handlePlayerInteraction(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_OPERATION]         = [](std::shared_ptr<Player> player, Packet& packet) { handlePartyOperation(player, packet); };
        m_packetHandlers[RecvOps::k_DENY_PARTY_REQUEST]      = [](std::shared_ptr<Player> player, Packet& packet) { handleDenyPartyRequest(player, packet); };
        m_packetHandlers[RecvOps::k_GUILD_OPERATION]         = [](std::shared_ptr<Player> player, Packet& packet) { handleGuildOperation(player, packet); };
        m_packetHandlers[RecvOps::k_DENY_GUILD_REQUEST]      = [](std::shared_ptr<Player> player, Packet& packet) { handleDenyGuildRequest(player, packet); };
        m_packetHandlers[RecvOps::k_BUDDY_LIST_MODIFY]       = [](std::shared_ptr<Player> player, Packet& packet) { handleBuddyListModify(player, packet); };
        m_packetHandlers[RecvOps::k_NOTE_ACTION]             = [](std::shared_ptr<Player> player, Packet& packet) { handleNoteAction(player, packet); };
        m_packetHandlers[RecvOps::k_USE_DOOR]                = [](std::shared_ptr<Player> player, Packet& packet) { handleUseDoor(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_KEY_MAP]          = [](std::shared_ptr<Player> player, Packet& packet) { handleChangeKeymap(player, packet); };
        m_packetHandlers[RecvOps::k_RING_ACTION]             = [](std::shared_ptr<Player> player, Packet& packet) { handleRingAction(player, packet); };
        m_packetHandlers[RecvOps::k_ALLIANCE_OPERATION]      = [](std::shared_ptr<Player> player, Packet& packet) { handleAllianceOperation(player, packet); };
        m_packetHandlers[RecvOps::k_BBS_OPERATION]           = [](std::shared_ptr<Player> player, Packet& packet) { handleBbsOperation(player, packet); };
        m_packetHandlers[RecvOps::k_ENTER_MTS]               = [](std::shared_ptr<Player> player, Packet& packet) { handleEnterMTS(player, packet); };
        m_packetHandlers[RecvOps::k_PET_TALK]                = [](std::shared_ptr<Player> player, Packet& packet) { handlePetTalk(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SOLOMAN_ITEM]        = [](std::shared_ptr<Player> player, Packet& packet) { handleUseSolomanItem(player, packet); };
        m_packetHandlers[RecvOps::k_PET_AUTO_POT]            = [](std::shared_ptr<Player> player, Packet& packet) { handlePetAutoPot(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_SUMMON]             = [](std::shared_ptr<Player> player, Packet& packet) { handleMoveSummon(player, packet); };
        m_packetHandlers[RecvOps::k_SUMMON_ATTACK]           = [](std::shared_ptr<Player> player, Packet& packet) { handleSummonAttack(player, packet); };
        m_packetHandlers[RecvOps::k_DAMAGE_SUMMON]           = [](std::shared_ptr<Player> player, Packet& packet) { handleDamageSummon(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_LIFE]               = [](std::shared_ptr<Player> player, Packet& packet) { handleMoveLife(player, packet); };
        m_packetHandlers[RecvOps::k_AUTO_AGGRO]              = [](std::shared_ptr<Player> player, Packet& packet) { handleAutoAggro(player, packet); };
        m_packetHandlers[RecvOps::k_MOB_DAMAGE_MOB]          = [](std::shared_ptr<Player> player, Packet& packet) { handleMobDamageMob(player, packet); };
        m_packetHandlers[RecvOps::k_MONSTER_BOMB]            = [](std::shared_ptr<Player> player, Packet& packet) { handleMonsterBomb(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_ACTION]              = [](std::shared_ptr<Player> player, Packet& packet) { handleNpcAction(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_PICKUP]             = [](std::shared_ptr<Player> player, Packet& packet) { handleItemPickup(player, packet); };
        m_packetHandlers[RecvOps::k_DAMAGE_REACTOR]          = [](std::shared_ptr<Player> player, Packet& packet) { handleDamageReactor(player, packet); };
        m_packetHandlers[RecvOps::k_MONSTER_CARNIVAL]        = [](std::shared_ptr<Player> player, Packet& packet) { handleMonsterCarnival(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_SEARCH_REGISTER]   = [](std::shared_ptr<Player> player, Packet& packet) { handlePartySearchRegister(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_SEARCH_START]      = [](std::shared_ptr<Player> player, Packet& packet) { handlePartySearchStart(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_UPDATE]           = [](std::shared_ptr<Player> player, Packet& packet) { handlePlayerUpdate(player, packet); };
        m_packetHandlers[RecvOps::k_MAPLE_TV]                = [](std::shared_ptr<Player> player, Packet& packet) { handleMapleTV(player, packet); };
        m_packetHandlers[RecvOps::k_MTS_OPERATION]           = [](std::shared_ptr<Player> player, Packet& packet) { handleMTSOperation(player, packet); };
        m_packetHandlers[RecvOps::k_TOUCHING_CS]             = [](std::shared_ptr<Player> player, Packet& packet) { handleTouchingCS(player, packet); };
        m_packetHandlers[RecvOps::k_BUY_CS_ITEM]             = [](std::shared_ptr<Player> player, Packet& packet) { handleBuyCSItem(player, packet); };
        m_packetHandlers[RecvOps::k_COUPON_CODE]             = [](std::shared_ptr<Player> player, Packet& packet) { handleCouponCode(player, packet); };
        m_packetHandlers[RecvOps::k_PET_SPAWN]               = [](std::shared_ptr<Player> player, Packet& packet) { handlePetSpawn(player, packet); };
        m_packetHandlers[RecvOps::k_PET_MOVE]                = [](std::shared_ptr<Player> player, Packet& packet) { handlePetMove(player, packet); };
        m_packetHandlers[RecvOps::k_PET_CHAT]                = [](std::shared_ptr<Player> player, Packet& packet) { handlePetChat(player, packet); };
        m_packetHandlers[RecvOps::k_PET_COMMAND]             = [](std::shared_ptr<Player> player, Packet& packet) { handlePetCommand(player, packet); };
        m_packetHandlers[RecvOps::k_PET_LOOT]                = [](std::shared_ptr<Player> player, Packet& packet) { handlePetLoot(player, packet); };
        m_packetHandlers[RecvOps::k_PET_FOOD]                = [](std::shared_ptr<Player> player, Packet& packet) { handlePetFood(player, packet); };
    }

    // GENERAL
    static void handlePong(std::shared_ptr<Player> player, Packet& packet) {}

    // LOGIN
    static void handleLoginPassword(std::shared_ptr<Player> player, Packet& packet);
    static inline void handleGuestLogin(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleGuestLogin"); }
    static inline void handleServerListRerequest(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleServerListRerequest"); }
    static void handleCharacterListRequest(std::shared_ptr<Player> player, Packet& packet);
    static void handleServerStatusRequest(std::shared_ptr<Player> player, Packet& packet);
    static inline void handleSetGender(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSetGender"); }
    static void handleAfterLogin(std::shared_ptr<Player> player, Packet& packet);
    static inline void handleRegisterPin(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleRegisterPin"); }
    static void handleServerListRequest(std::shared_ptr<Player> player, Packet& packet);
    static inline void handlePlayerDC(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePlayerDC"); }
    static inline void handleViewAllChar(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleViewAllChar"); }
    static inline void handlePickAllChar(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePickAllChar"); }
    static inline void handleCharSelect(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCharSelect"); }
    static void handleCheckCharacterName(std::shared_ptr<Player> player, Packet& packet);
    static inline void handleCreateChar(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCreateChar"); }
    static inline void handleDeleteChar(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDeleteChar"); }
    static inline void handleClientStart(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleClientStart"); }
    static inline void handleRelog(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleRelog"); }

    // CHANNEL
    static inline void handlePlayerLoggedIn(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePlayerLoggedIn"); }
    static inline void handleStrangeData(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleStrangeData"); }
    static inline void handleChangeMap(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleChangeMap"); }
    static inline void handleChangeChannel(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleChangeChannel"); }
    static inline void handleEnterCashShop(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleEnterCashShop"); }
    static inline void handleMovePlayer(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMovePlayer"); }
    static inline void handleCancelChair(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCancelChair"); }
    static inline void handleUseChair(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseChair"); }
    static inline void handleCloseRangeAttack(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCloseRangeAttack"); }
    static inline void handleRangedAttack(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleRangedAttack"); }
    static inline void handleMagicAttack(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMagicAttack"); }
    static inline void handleEnergyOrbAttack(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleEnergyOrbAttack"); }
    static inline void handleTakeDamage(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleTakeDamage"); }
    static inline void handleGeneralChat(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleGeneralChat"); }
    static inline void handleCloseChalkboard(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCloseChalkboard"); }
    static inline void handleFaceExpression(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleFaceExpression"); }
    static inline void handleUseItemEffect(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseItemEffect"); }
    static inline void handleNpcTalk(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleNpcTalk"); }
    static inline void handleNpcTalkMore(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleNpcTalkMore"); }
    static inline void handleNpcShop(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleNpcShop"); }
    static inline void handleStorage(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleStorage"); }
    static inline void handleHiredMerchantRequest(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleHiredMerchantRequest"); }
    static inline void handleDueyAction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDueyAction"); }
    static inline void handleItemSort(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleItemSort"); }
    static inline void handleItemSort2(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleItemSort2"); }
    static inline void handleItemMove(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleItemMove"); }
    static inline void handleUseItem(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseItem"); }
    static inline void handleCancelItemEffect(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCancelItemEffect"); }
    static inline void handleUseSummonBag(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseSummonBag"); }
    static inline void handleUseMountFood(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseMountFood"); }
    static inline void handleUseCashItem(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseCashItem"); }
    static inline void handleUseCatchItem(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseCatchItem"); }
    static inline void handleUseSkillBook(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseSkillBook"); }
    static inline void handleUseReturnScroll(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseReturnScroll"); }
    static inline void handleUseUpgradeScroll(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseUpgradeScroll"); }
    static inline void handleDistributeAP(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDistributeAP"); }
    static inline void handleHealOverTime(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleHealOverTime"); }
    static inline void handleDistributeSP(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDistributeSP"); }
    static inline void handleSpecialMove(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSpecialMove"); }
    static inline void handleCancelBuff(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCancelBuff"); }
    static inline void handleSkillEffect(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSkillEffect"); }
    static inline void handleMesoDrop(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMesoDrop"); }
    static inline void handleGiveFame(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleGiveFame"); }
    static inline void handleCharInfoRequest(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCharInfoRequest"); }
    static inline void handleCancelDebuff(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCancelDebuff"); }
    static inline void handleChangeMapSpecial(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleChangeMapSpecial"); }
    static inline void handleUseInnerPortal(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseInnerPortal"); }
    static inline void handleVipAddMap(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleVipAddMap"); }
    static inline void handleQuestAction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleQuestAction"); }
    static inline void handleSkillMacro(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSkillMacro"); }
    static inline void handleReportPlayer(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleReportPlayer"); }
    static inline void handlePartyChat(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePartyChat"); }
    static inline void handleWhisper(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleWhisper"); }
    static inline void handleSpouseChat(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSpouseChat"); }
    static inline void handleMessenger(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMessenger"); }
    static inline void handlePlayerShop(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePlayerShop"); }
    static inline void handlePlayerInteraction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePlayerInteraction"); }
    static inline void handlePartyOperation(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePartyOperation"); }
    static inline void handleDenyPartyRequest(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDenyPartyRequest"); }
    static inline void handleGuildOperation(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleGuildOperation"); }
    static inline void handleDenyGuildRequest(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDenyGuildRequest"); }
    static inline void handleBuddyListModify(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleBuddyListModify"); }
    static inline void handleNoteAction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleNoteAction"); }
    static inline void handleUseDoor(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseDoor"); }
    static inline void handleChangeKeymap(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleChangeKeymap"); }
    static inline void handleRingAction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleRingAction"); }
    static inline void handleAllianceOperation(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleAllianceOperation"); }
    static inline void handleBbsOperation(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleBbsOperation"); }
    static inline void handleEnterMTS(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleEnterMTS"); }
    static inline void handlePetTalk(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetTalk"); }
    static inline void handleUseSolomanItem(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleUseSolomanItem"); }
    static inline void handlePetAutoPot(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetAutoPot"); }
    static inline void handleMoveSummon(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMoveSummon"); }
    static inline void handleSummonAttack(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleSummonAttack"); }
    static inline void handleDamageSummon(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDamageSummon"); }
    static inline void handleMoveLife(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMoveLife"); }
    static inline void handleAutoAggro(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleAutoAggro"); }
    static inline void handleMobDamageMob(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMobDamageMob"); }
    static inline void handleMonsterBomb(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMonsterBomb"); }
    static inline void handleNpcAction(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleNpcAction"); }
    static inline void handleItemPickup(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleItemPickup"); }
    static inline void handleDamageReactor(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleDamageReactor"); }
    static inline void handleMonsterCarnival(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMonsterCarnival"); }
    static inline void handlePartySearchRegister(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePartySearchRegister"); }
    static inline void handlePartySearchStart(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePartySearchStart"); }
    static inline void handlePlayerUpdate(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePlayerUpdate"); }
    static inline void handleMapleTV(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMapleTV"); }
    static inline void handleMTSOperation(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleMTSOperation"); }
    static inline void handleTouchingCS(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleTouchingCS"); }
    static inline void handleBuyCSItem(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleBuyCSItem"); }
    static inline void handleCouponCode(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handleCouponCode"); }
    static inline void handlePetSpawn(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetSpawn"); }
    static inline void handlePetMove(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetMove"); }
    static inline void handlePetChat(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetChat"); }
    static inline void handlePetCommand(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetCommand"); }
    static inline void handlePetLoot(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetLoot"); }
    static inline void handlePetFood(std::shared_ptr<Player> player, Packet& packet) { SERVER_INFO("handlePetFood"); }

public:
    static inline PacketHandlers m_packetHandlers;
};