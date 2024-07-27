#pragma once

#include "Typedefs.h"
#include "game/Player.h"
#include "net/packets/PacketConstants.h"

class PacketHandler
{
public:
    PacketHandler() = delete;

    static inline void initialize()
    {
        // GENERAL
        m_packetHandlers[RecvOps::k_PONG] = [](Player& player, Packet& packet) { handlePong(player, packet); };

        // LOGIN
        m_packetHandlers[RecvOps::k_LOGIN_PASSWORD] = [](Player& player, Packet& packet) { handleLoginPassword(player, packet); };
        m_packetHandlers[RecvOps::k_GUEST_LOGIN] = [](Player& player, Packet& packet) { handleGuestLogin(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_LIST_REREQUEST] = [](Player& player, Packet& packet) { handleServerListRerequest(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_LIST_REQUEST] = [](Player& player, Packet& packet) { handleCharListRequest(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_STATUS_REQUEST] = [](Player& player, Packet& packet) { handleServerStatusRequest(player, packet); };
        m_packetHandlers[RecvOps::k_SET_GENDER] = [](Player& player, Packet& packet) { handleSetGender(player, packet); };
        m_packetHandlers[RecvOps::k_AFTER_LOGIN] = [](Player& player, Packet& packet) { handleAfterLogin(player, packet); };
        m_packetHandlers[RecvOps::k_REGISTER_PIN] = [](Player& player, Packet& packet) { handleRegisterPin(player, packet); };
        m_packetHandlers[RecvOps::k_SERVER_LIST_REQUEST] = [](Player& player, Packet& packet) { handleServerListRequest(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_DC] = [](Player& player, Packet& packet) { handlePlayerDC(player, packet); };
        m_packetHandlers[RecvOps::k_VIEW_ALL_CHAR] = [](Player& player, Packet& packet) { handleViewAllChar(player, packet); };
        m_packetHandlers[RecvOps::k_PICK_ALL_CHAR] = [](Player& player, Packet& packet) { handlePickAllChar(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_SELECT] = [](Player& player, Packet& packet) { handleCharSelect(player, packet); };
        m_packetHandlers[RecvOps::k_CHECK_CHAR_NAME] = [](Player& player, Packet& packet) { handleCheckCharName(player, packet); };
        m_packetHandlers[RecvOps::k_CREATE_CHAR] = [](Player& player, Packet& packet) { handleCreateChar(player, packet); };
        m_packetHandlers[RecvOps::k_DELETE_CHAR] = [](Player& player, Packet& packet) { handleDeleteChar(player, packet); };
        m_packetHandlers[RecvOps::k_CLIENT_START] = [](Player& player, Packet& packet) { handleClientStart(player, packet); };
        m_packetHandlers[RecvOps::k_RELOG] = [](Player& player, Packet& packet) { handleRelog(player, packet); };

        // CHANNEL
        m_packetHandlers[RecvOps::k_PLAYER_LOGGED_IN] = [](Player& player, Packet& packet) { handlePlayerLoggedIn(player, packet); };
        m_packetHandlers[RecvOps::k_STRANGE_DATA] = [](Player& player, Packet& packet) { handleStrangeData(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_MAP] = [](Player& player, Packet& packet) { handleChangeMap(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_CHANNEL] = [](Player& player, Packet& packet) { handleChangeChannel(player, packet); };
        m_packetHandlers[RecvOps::k_ENTER_CASH_SHOP] = [](Player& player, Packet& packet) { handleEnterCashShop(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_PLAYER] = [](Player& player, Packet& packet) { handleMovePlayer(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_CHAIR] = [](Player& player, Packet& packet) { handleCancelChair(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CHAIR] = [](Player& player, Packet& packet) { handleUseChair(player, packet); };
        m_packetHandlers[RecvOps::k_CLOSE_RANGE_ATTACK] = [](Player& player, Packet& packet) { handleCloseRangeAttack(player, packet); };
        m_packetHandlers[RecvOps::k_RANGED_ATTACK] = [](Player& player, Packet& packet) { handleRangedAttack(player, packet); };
        m_packetHandlers[RecvOps::k_MAGIC_ATTACK] = [](Player& player, Packet& packet) { handleMagicAttack(player, packet); };
        m_packetHandlers[RecvOps::k_ENERGY_ORB_ATTACK] = [](Player& player, Packet& packet) { handleEnergyOrbAttack(player, packet); };
        m_packetHandlers[RecvOps::k_TAKE_DAMAGE] = [](Player& player, Packet& packet) { handleTakeDamage(player, packet); };
        m_packetHandlers[RecvOps::k_GENERAL_CHAT] = [](Player& player, Packet& packet) { handleGeneralChat(player, packet); };
        m_packetHandlers[RecvOps::k_CLOSE_CHALKBOARD] = [](Player& player, Packet& packet) { handleCloseChalkboard(player, packet); };
        m_packetHandlers[RecvOps::k_FACE_EXPRESSION] = [](Player& player, Packet& packet) { handleFaceExpression(player, packet); };
        m_packetHandlers[RecvOps::k_USE_ITEM_EFFECT] = [](Player& player, Packet& packet) { handleUseItemEffect(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_TALK] = [](Player& player, Packet& packet) { handleNpcTalk(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_TALK_MORE] = [](Player& player, Packet& packet) { handleNpcTalkMore(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_SHOP] = [](Player& player, Packet& packet) { handleNpcShop(player, packet); };
        m_packetHandlers[RecvOps::k_STORAGE] = [](Player& player, Packet& packet) { handleStorage(player, packet); };
        m_packetHandlers[RecvOps::k_HIRED_MERCHANT_REQUEST] = [](Player& player, Packet& packet) { handleHiredMerchantRequest(player, packet); };
        m_packetHandlers[RecvOps::k_DUEY_ACTION] = [](Player& player, Packet& packet) { handleDueyAction(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_SORT] = [](Player& player, Packet& packet) { handleItemSort(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_SORT2] = [](Player& player, Packet& packet) { handleItemSort2(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_MOVE] = [](Player& player, Packet& packet) { handleItemMove(player, packet); };
        m_packetHandlers[RecvOps::k_USE_ITEM] = [](Player& player, Packet& packet) { handleUseItem(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_ITEM_EFFECT] = [](Player& player, Packet& packet) { handleCancelItemEffect(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SUMMON_BAG] = [](Player& player, Packet& packet) { handleUseSummonBag(player, packet); };
        m_packetHandlers[RecvOps::k_USE_MOUNT_FOOD] = [](Player& player, Packet& packet) { handleUseMountFood(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CASH_ITEM] = [](Player& player, Packet& packet) { handleUseCashItem(player, packet); };
        m_packetHandlers[RecvOps::k_USE_CATCH_ITEM] = [](Player& player, Packet& packet) { handleUseCatchItem(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SKILL_BOOK] = [](Player& player, Packet& packet) { handleUseSkillBook(player, packet); };
        m_packetHandlers[RecvOps::k_USE_RETURN_SCROLL] = [](Player& player, Packet& packet) { handleUseReturnScroll(player, packet); };
        m_packetHandlers[RecvOps::k_USE_UPGRADE_SCROLL] = [](Player& player, Packet& packet) { handleUseUpgradeScroll(player, packet); };
        m_packetHandlers[RecvOps::k_DISTRIBUTE_AP] = [](Player& player, Packet& packet) { handleDistributeAP(player, packet); };
        m_packetHandlers[RecvOps::k_HEAL_OVER_TIME] = [](Player& player, Packet& packet) { handleHealOverTime(player, packet); };
        m_packetHandlers[RecvOps::k_DISTRIBUTE_SP] = [](Player& player, Packet& packet) { handleDistributeSP(player, packet); };
        m_packetHandlers[RecvOps::k_SPECIAL_MOVE] = [](Player& player, Packet& packet) { handleSpecialMove(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_BUFF] = [](Player& player, Packet& packet) { handleCancelBuff(player, packet); };
        m_packetHandlers[RecvOps::k_SKILL_EFFECT] = [](Player& player, Packet& packet) { handleSkillEffect(player, packet); };
        m_packetHandlers[RecvOps::k_MESO_DROP] = [](Player& player, Packet& packet) { handleMesoDrop(player, packet); };
        m_packetHandlers[RecvOps::k_GIVE_FAME] = [](Player& player, Packet& packet) { handleGiveFame(player, packet); };
        m_packetHandlers[RecvOps::k_CHAR_INFO_REQUEST] = [](Player& player, Packet& packet) { handleCharInfoRequest(player, packet); };
        m_packetHandlers[RecvOps::k_CANCEL_DEBUFF] = [](Player& player, Packet& packet) { handleCancelDebuff(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_MAP_SPECIAL] = [](Player& player, Packet& packet) { handleChangeMapSpecial(player, packet); };
        m_packetHandlers[RecvOps::k_USE_INNER_PORTAL] = [](Player& player, Packet& packet) { handleUseInnerPortal(player, packet); };
        m_packetHandlers[RecvOps::k_VIP_ADD_MAP] = [](Player& player, Packet& packet) { handleVipAddMap(player, packet); };
        m_packetHandlers[RecvOps::k_QUEST_ACTION] = [](Player& player, Packet& packet) { handleQuestAction(player, packet); };
        m_packetHandlers[RecvOps::k_SKILL_MACRO] = [](Player& player, Packet& packet) { handleSkillMacro(player, packet); };
        m_packetHandlers[RecvOps::k_REPORT_PLAYER] = [](Player& player, Packet& packet) { handleReportPlayer(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_CHAT] = [](Player& player, Packet& packet) { handlePartyChat(player, packet); };
        m_packetHandlers[RecvOps::k_WHISPER] = [](Player& player, Packet& packet) { handleWhisper(player, packet); };
        m_packetHandlers[RecvOps::k_SPOUSE_CHAT] = [](Player& player, Packet& packet) { handleSpouseChat(player, packet); };
        m_packetHandlers[RecvOps::k_MESSENGER] = [](Player& player, Packet& packet) { handleMessenger(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_SHOP] = [](Player& player, Packet& packet) { handlePlayerShop(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_INTERACTION] = [](Player& player, Packet& packet) { handlePlayerInteraction(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_OPERATION] = [](Player& player, Packet& packet) { handlePartyOperation(player, packet); };
        m_packetHandlers[RecvOps::k_DENY_PARTY_REQUEST] = [](Player& player, Packet& packet) { handleDenyPartyRequest(player, packet); };
        m_packetHandlers[RecvOps::k_GUILD_OPERATION] = [](Player& player, Packet& packet) { handleGuildOperation(player, packet); };
        m_packetHandlers[RecvOps::k_DENY_GUILD_REQUEST] = [](Player& player, Packet& packet) { handleDenyGuildRequest(player, packet); };
        m_packetHandlers[RecvOps::k_BUDDY_LIST_MODIFY] = [](Player& player, Packet& packet) { handleBuddyListModify(player, packet); };
        m_packetHandlers[RecvOps::k_NOTE_ACTION] = [](Player& player, Packet& packet) { handleNoteAction(player, packet); };
        m_packetHandlers[RecvOps::k_USE_DOOR] = [](Player& player, Packet& packet) { handleUseDoor(player, packet); };
        m_packetHandlers[RecvOps::k_CHANGE_KEY_MAP] = [](Player& player, Packet& packet) { handleChangeKeymap(player, packet); };
        m_packetHandlers[RecvOps::k_RING_ACTION] = [](Player& player, Packet& packet) { handleRingAction(player, packet); };
        m_packetHandlers[RecvOps::k_ALLIANCE_OPERATION] = [](Player& player, Packet& packet) { handleAllianceOperation(player, packet); };
        m_packetHandlers[RecvOps::k_BBS_OPERATION] = [](Player& player, Packet& packet) { handleBbsOperation(player, packet); };
        m_packetHandlers[RecvOps::k_ENTER_MTS] = [](Player& player, Packet& packet) { handleEnterMTS(player, packet); };
        m_packetHandlers[RecvOps::k_PET_TALK] = [](Player& player, Packet& packet) { handlePetTalk(player, packet); };
        m_packetHandlers[RecvOps::k_USE_SOLOMAN_ITEM] = [](Player& player, Packet& packet) { handleUseSolomanItem(player, packet); };
        m_packetHandlers[RecvOps::k_PET_AUTO_POT] = [](Player& player, Packet& packet) { handlePetAutoPot(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_SUMMON] = [](Player& player, Packet& packet) { handleMoveSummon(player, packet); };
        m_packetHandlers[RecvOps::k_SUMMON_ATTACK] = [](Player& player, Packet& packet) { handleSummonAttack(player, packet); };
        m_packetHandlers[RecvOps::k_DAMAGE_SUMMON] = [](Player& player, Packet& packet) { handleDamageSummon(player, packet); };
        m_packetHandlers[RecvOps::k_MOVE_LIFE] = [](Player& player, Packet& packet) { handleMoveLife(player, packet); };
        m_packetHandlers[RecvOps::k_AUTO_AGGRO] = [](Player& player, Packet& packet) { handleAutoAggro(player, packet); };
        m_packetHandlers[RecvOps::k_MOB_DAMAGE_MOB] = [](Player& player, Packet& packet) { handleMobDamageMob(player, packet); };
        m_packetHandlers[RecvOps::k_MONSTER_BOMB] = [](Player& player, Packet& packet) { handleMonsterBomb(player, packet); };
        m_packetHandlers[RecvOps::k_NPC_ACTION] = [](Player& player, Packet& packet) { handleNpcAction(player, packet); };
        m_packetHandlers[RecvOps::k_ITEM_PICKUP] = [](Player& player, Packet& packet) { handleItemPickup(player, packet); };
        m_packetHandlers[RecvOps::k_DAMAGE_REACTOR] = [](Player& player, Packet& packet) { handleDamageReactor(player, packet); };
        m_packetHandlers[RecvOps::k_MONSTER_CARNIVAL] = [](Player& player, Packet& packet) { handleMonsterCarnival(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_SEARCH_REGISTER] = [](Player& player, Packet& packet) { handlePartySearchRegister(player, packet); };
        m_packetHandlers[RecvOps::k_PARTY_SEARCH_START] = [](Player& player, Packet& packet) { handlePartySearchStart(player, packet); };
        m_packetHandlers[RecvOps::k_PLAYER_UPDATE] = [](Player& player, Packet& packet) { handlePlayerUpdate(player, packet); };
        m_packetHandlers[RecvOps::k_MAPLE_TV] = [](Player& player, Packet& packet) { handleMapleTV(player, packet); };
        m_packetHandlers[RecvOps::k_MTS_OPERATION] = [](Player& player, Packet& packet) { handleMTSOperation(player, packet); };
        m_packetHandlers[RecvOps::k_TOUCHING_CS] = [](Player& player, Packet& packet) { handleTouchingCS(player, packet); };
        m_packetHandlers[RecvOps::k_BUY_CS_ITEM] = [](Player& player, Packet& packet) { handleBuyCSItem(player, packet); };
        m_packetHandlers[RecvOps::k_COUPON_CODE] = [](Player& player, Packet& packet) { handleCouponCode(player, packet); };
        m_packetHandlers[RecvOps::k_PET_SPAWN] = [](Player& player, Packet& packet) { handlePetSpawn(player, packet); };
        m_packetHandlers[RecvOps::k_PET_MOVE] = [](Player& player, Packet& packet) { handlePetMove(player, packet); };
        m_packetHandlers[RecvOps::k_PET_CHAT] = [](Player& player, Packet& packet) { handlePetChat(player, packet); };
        m_packetHandlers[RecvOps::k_PET_COMMAND] = [](Player& player, Packet& packet) { handlePetCommand(player, packet); };
        m_packetHandlers[RecvOps::k_PET_LOOT] = [](Player& player, Packet& packet) { handlePetLoot(player, packet); };
        m_packetHandlers[RecvOps::k_PET_FOOD] = [](Player& player, Packet& packet) { handlePetFood(player, packet); };
    }

    // GENERAL
    static void handlePong(Player& player, Packet& packet);

    // LOGIN
    static void handleLoginPassword(Player& player, Packet& packet);
    static void handleGuestLogin(Player& player, Packet& packet);
    static void handleServerListRerequest(Player& player, Packet& packet);
    static void handleCharListRequest(Player& player, Packet& packet);
    static void handleServerStatusRequest(Player& player, Packet& packet);
    static void handleSetGender(Player& player, Packet& packet);
    static void handleAfterLogin(Player& player, Packet& packet);
    static void handleRegisterPin(Player& player, Packet& packet);
    static void handleServerListRequest(Player& player, Packet& packet);
    static void handlePlayerDC(Player& player, Packet& packet);
    static void handleViewAllChar(Player& player, Packet& packet);
    static void handlePickAllChar(Player& player, Packet& packet);
    static void handleCharSelect(Player& player, Packet& packet);
    static void handleCheckCharName(Player& player, Packet& packet);
    static void handleCreateChar(Player& player, Packet& packet);
    static void handleDeleteChar(Player& player, Packet& packet);
    static void handleClientStart(Player& player, Packet& packet);
    static void handleRelog(Player& player, Packet& packet);

    // CHANNEL
    static inline void handlePlayerLoggedIn(Player& player, Packet& packet) {}
    static inline void handleStrangeData(Player& player, Packet& packet) {}
    static inline void handleChangeMap(Player& player, Packet& packet) {}
    static inline void handleChangeChannel(Player& player, Packet& packet) {}
    static inline void handleEnterCashShop(Player& player, Packet& packet) {}
    static inline void handleMovePlayer(Player& player, Packet& packet) {}
    static inline void handleCancelChair(Player& player, Packet& packet) {}
    static inline void handleUseChair(Player& player, Packet& packet) {}
    static inline void handleCloseRangeAttack(Player& player, Packet& packet) {}
    static inline void handleRangedAttack(Player& player, Packet& packet) {}
    static inline void handleMagicAttack(Player& player, Packet& packet) {}
    static inline void handleEnergyOrbAttack(Player& player, Packet& packet) {}
    static inline void handleTakeDamage(Player& player, Packet& packet) {}
    static inline void handleGeneralChat(Player& player, Packet& packet) {}
    static inline void handleCloseChalkboard(Player& player, Packet& packet) {}
    static inline void handleFaceExpression(Player& player, Packet& packet) {}
    static inline void handleUseItemEffect(Player& player, Packet& packet) {}
    static inline void handleNpcTalk(Player& player, Packet& packet) {}
    static inline void handleNpcTalkMore(Player& player, Packet& packet) {}
    static inline void handleNpcShop(Player& player, Packet& packet) {}
    static inline void handleStorage(Player& player, Packet& packet) {}
    static inline void handleHiredMerchantRequest(Player& player, Packet& packet) {}
    static inline void handleDueyAction(Player& player, Packet& packet) {}
    static inline void handleItemSort(Player& player, Packet& packet) {}
    static inline void handleItemSort2(Player& player, Packet& packet) {}
    static inline void handleItemMove(Player& player, Packet& packet) {}
    static inline void handleUseItem(Player& player, Packet& packet) {}
    static inline void handleCancelItemEffect(Player& player, Packet& packet) {}
    static inline void handleUseSummonBag(Player& player, Packet& packet) {}
    static inline void handleUseMountFood(Player& player, Packet& packet) {}
    static inline void handleUseCashItem(Player& player, Packet& packet) {}
    static inline void handleUseCatchItem(Player& player, Packet& packet) {}
    static inline void handleUseSkillBook(Player& player, Packet& packet) {}
    static inline void handleUseReturnScroll(Player& player, Packet& packet) {}
    static inline void handleUseUpgradeScroll(Player& player, Packet& packet) {}
    static inline void handleDistributeAP(Player& player, Packet& packet) {}
    static inline void handleHealOverTime(Player& player, Packet& packet) {}
    static inline void handleDistributeSP(Player& player, Packet& packet) {}
    static inline void handleSpecialMove(Player& player, Packet& packet) {}
    static inline void handleCancelBuff(Player& player, Packet& packet) {}
    static inline void handleSkillEffect(Player& player, Packet& packet) {}
    static inline void handleMesoDrop(Player& player, Packet& packet) {}
    static inline void handleGiveFame(Player& player, Packet& packet) {}
    static inline void handleCharInfoRequest(Player& player, Packet& packet) {}
    static inline void handleCancelDebuff(Player& player, Packet& packet) {}
    static inline void handleChangeMapSpecial(Player& player, Packet& packet) {}
    static inline void handleUseInnerPortal(Player& player, Packet& packet) {}
    static inline void handleVipAddMap(Player& player, Packet& packet) {}
    static inline void handleQuestAction(Player& player, Packet& packet) {}
    static inline void handleSkillMacro(Player& player, Packet& packet) {}
    static inline void handleReportPlayer(Player& player, Packet& packet) {}
    static inline void handlePartyChat(Player& player, Packet& packet) {}
    static inline void handleWhisper(Player& player, Packet& packet) {}
    static inline void handleSpouseChat(Player& player, Packet& packet) {}
    static inline void handleMessenger(Player& player, Packet& packet) {}
    static inline void handlePlayerShop(Player& player, Packet& packet) {}
    static inline void handlePlayerInteraction(Player& player, Packet& packet) {}
    static inline void handlePartyOperation(Player& player, Packet& packet) {}
    static inline void handleDenyPartyRequest(Player& player, Packet& packet) {}
    static inline void handleGuildOperation(Player& player, Packet& packet) {}
    static inline void handleDenyGuildRequest(Player& player, Packet& packet) {}
    static inline void handleBuddyListModify(Player& player, Packet& packet) {}
    static inline void handleNoteAction(Player& player, Packet& packet) {}
    static inline void handleUseDoor(Player& player, Packet& packet) {}
    static inline void handleChangeKeymap(Player& player, Packet& packet) {}
    static inline void handleRingAction(Player& player, Packet& packet) {}
    static inline void handleAllianceOperation(Player& player, Packet& packet) {}
    static inline void handleBbsOperation(Player& player, Packet& packet) {}
    static inline void handleEnterMTS(Player& player, Packet& packet) {}
    static inline void handlePetTalk(Player& player, Packet& packet) {}
    static inline void handleUseSolomanItem(Player& player, Packet& packet) {}
    static inline void handlePetAutoPot(Player& player, Packet& packet) {}
    static inline void handleMoveSummon(Player& player, Packet& packet) {}
    static inline void handleSummonAttack(Player& player, Packet& packet) {}
    static inline void handleDamageSummon(Player& player, Packet& packet) {}
    static inline void handleMoveLife(Player& player, Packet& packet) {}
    static inline void handleAutoAggro(Player& player, Packet& packet) {}
    static inline void handleMobDamageMob(Player& player, Packet& packet) {}
    static inline void handleMonsterBomb(Player& player, Packet& packet) {}
    static inline void handleNpcAction(Player& player, Packet& packet) {}
    static inline void handleItemPickup(Player& player, Packet& packet) {}
    static inline void handleDamageReactor(Player& player, Packet& packet) {}
    static inline void handleMonsterCarnival(Player& player, Packet& packet) {}
    static inline void handlePartySearchRegister(Player& player, Packet& packet) {}
    static inline void handlePartySearchStart(Player& player, Packet& packet) {}
    static inline void handlePlayerUpdate(Player& player, Packet& packet) {}
    static inline void handleMapleTV(Player& player, Packet& packet) {}
    static inline void handleMTSOperation(Player& player, Packet& packet) {}
    static inline void handleTouchingCS(Player& player, Packet& packet) {}
    static inline void handleBuyCSItem(Player& player, Packet& packet) {}
    static inline void handleCouponCode(Player& player, Packet& packet) {}
    static inline void handlePetSpawn(Player& player, Packet& packet) {}
    static inline void handlePetMove(Player& player, Packet& packet) {}
    static inline void handlePetChat(Player& player, Packet& packet) {}
    static inline void handlePetCommand(Player& player, Packet& packet) {}
    static inline void handlePetLoot(Player& player, Packet& packet) {}
    static inline void handlePetFood(Player& player, Packet& packet) {}

public:
    static inline PacketHandlers m_packetHandlers;
};