

#include "PacketHandler.h"
#include "game/Player.h"

#include "net/packets/PacketConstants.h"

PacketHandlers PacketHandler::m_packetHandlers;

void PacketHandler::registerHandlers()
{
    // GENERAL
    m_packetHandlers[RecvOps::k_PONG]                   = [](Player& player, Packet& packet) { handlePong(player, packet); };

    // LOGIN
    m_packetHandlers[RecvOps::k_LOGIN_PASSWORD]         = [](Player& player, Packet& packet) { handleLoginPassword(player, packet); };
    m_packetHandlers[RecvOps::k_GUEST_LOGIN]            = [](Player& player, Packet& packet) { handleGuestLogin(player, packet); };
    m_packetHandlers[RecvOps::k_SERVER_LIST_REREQUEST]  = [](Player& player, Packet& packet) { handleServerListRerequest(player, packet); };
    m_packetHandlers[RecvOps::k_CHAR_LIST_REQUEST]      = [](Player& player, Packet& packet) { handleCharListRequest(player, packet); };
    m_packetHandlers[RecvOps::k_SERVER_STATUS_REQUEST]  = [](Player& player, Packet& packet) { handleServerStatusRequest(player, packet); };
    m_packetHandlers[RecvOps::k_SET_GENDER]             = [](Player& player, Packet& packet) { handleSetGender(player, packet); };
    m_packetHandlers[RecvOps::k_AFTER_LOGIN]            = [](Player& player, Packet& packet) { handleAfterLogin(player, packet); };
    m_packetHandlers[RecvOps::k_REGISTER_PIN]           = [](Player& player, Packet& packet) { handleRegisterPin(player, packet); };
    m_packetHandlers[RecvOps::k_SERVER_LIST_REQUEST]    = [](Player& player, Packet& packet) { handleServerListRequest(player, packet); };
    m_packetHandlers[RecvOps::k_PLAYER_DC]              = [](Player& player, Packet& packet) { handlePlayerDC(player, packet); };
    m_packetHandlers[RecvOps::k_VIEW_ALL_CHAR]          = [](Player& player, Packet& packet) { handleViewAllChar(player, packet); };
    m_packetHandlers[RecvOps::k_PICK_ALL_CHAR]          = [](Player& player, Packet& packet) { handlePickAllChar(player, packet); };
    m_packetHandlers[RecvOps::k_CHAR_SELECT]            = [](Player& player, Packet& packet) { handleCharSelect(player, packet); };
    m_packetHandlers[RecvOps::k_CHECK_CHAR_NAME]        = [](Player& player, Packet& packet) { handleCheckCharName(player, packet); };
    m_packetHandlers[RecvOps::k_CREATE_CHAR]            = [](Player& player, Packet& packet) { handleCreateChar(player, packet); };
    m_packetHandlers[RecvOps::k_DELETE_CHAR]            = [](Player& player, Packet& packet) { handleDeleteChar(player, packet); };
    m_packetHandlers[RecvOps::k_CLIENT_START]           = [](Player& player, Packet& packet) { handleClientStart(player, packet); };
    m_packetHandlers[RecvOps::k_RELOG]                  = [](Player& player, Packet& packet) { handleRelog(player, packet); };

    // CHANNEL
    m_packetHandlers[RecvOps::k_PLAYER_LOGGED_IN]       = [](Player& player, Packet& packet) { handlePlayerLoggedIn(player, packet); };
    m_packetHandlers[RecvOps::k_STRANGE_DATA]           = [](Player& player, Packet& packet) { handleStrangeData(player, packet); };
    m_packetHandlers[RecvOps::k_CHANGE_MAP]             = [](Player& player, Packet& packet) { handleChangeMap(player, packet); };
    m_packetHandlers[RecvOps::k_CHANGE_CHANNEL]         = [](Player& player, Packet& packet) { handleChangeChannel(player, packet); };
    m_packetHandlers[RecvOps::k_ENTER_CASH_SHOP]        = [](Player& player, Packet& packet) { handleEnterCashShop(player, packet); };
    m_packetHandlers[RecvOps::k_MOVE_PLAYER]            = [](Player& player, Packet& packet) { handleMovePlayer(player, packet); };
    m_packetHandlers[RecvOps::k_CANCEL_CHAIR]           = [](Player& player, Packet& packet) { handleCancelChair(player, packet); };
    m_packetHandlers[RecvOps::k_USE_CHAIR]              = [](Player& player, Packet& packet) { handleUseChair(player, packet); };
    m_packetHandlers[RecvOps::k_CLOSE_RANGE_ATTACK]     = [](Player& player, Packet& packet) { handleCloseRangeAttack(player, packet); };
    m_packetHandlers[RecvOps::k_RANGED_ATTACK]          = [](Player& player, Packet& packet) { handleRangedAttack(player, packet); };
    m_packetHandlers[RecvOps::k_MAGIC_ATTACK]           = [](Player& player, Packet& packet) { handleMagicAttack(player, packet); };
    m_packetHandlers[RecvOps::k_ENERGY_ORB_ATTACK]      = [](Player& player, Packet& packet) { handleEnergyOrbAttack(player, packet); };
    m_packetHandlers[RecvOps::k_TAKE_DAMAGE]            = [](Player& player, Packet& packet) { handleTakeDamage(player, packet); };
    m_packetHandlers[RecvOps::k_GENERAL_CHAT]           = [](Player& player, Packet& packet) { handleGeneralChat(player, packet); };
    m_packetHandlers[RecvOps::k_CLOSE_CHALKBOARD]       = [](Player& player, Packet& packet) { handleCloseChalkboard(player, packet); };
    m_packetHandlers[RecvOps::k_FACE_EXPRESSION]        = [](Player& player, Packet& packet) { handleFaceExpression(player, packet); };
    m_packetHandlers[RecvOps::k_USE_ITEM_EFFECT]        = [](Player& player, Packet& packet) { handleUseItemEffect(player, packet); };
    m_packetHandlers[RecvOps::k_NPC_TALK]               = [](Player& player, Packet& packet) { handleNpcTalk(player, packet); };
    m_packetHandlers[RecvOps::k_NPC_TALK_MORE]          = [](Player& player, Packet& packet) { handleNpcTalkMore(player, packet); };
    m_packetHandlers[RecvOps::k_NPC_SHOP]               = [](Player& player, Packet& packet) { handleNpcShop(player, packet); };
    m_packetHandlers[RecvOps::k_STORAGE]                = [](Player& player, Packet& packet) { handleStorage(player, packet); };
    m_packetHandlers[RecvOps::k_HIRED_MERCHANT_REQUEST] = [](Player& player, Packet& packet) { handleHiredMerchantRequest(player, packet); };
    m_packetHandlers[RecvOps::k_DUEY_ACTION]            = [](Player& player, Packet& packet) { handleDueyAction(player, packet); };
    m_packetHandlers[RecvOps::k_ITEM_SORT]              = [](Player& player, Packet& packet) { handleItemSort(player, packet); };
    m_packetHandlers[RecvOps::k_ITEM_SORT2]             = [](Player& player, Packet& packet) { handleItemSort2(player, packet); };
    m_packetHandlers[RecvOps::k_ITEM_MOVE]              = [](Player& player, Packet& packet) { handleItemMove(player, packet); };
    m_packetHandlers[RecvOps::k_USE_ITEM]               = [](Player& player, Packet& packet) { handleUseItem(player, packet); };
    m_packetHandlers[RecvOps::k_CANCEL_ITEM_EFFECT]     = [](Player& player, Packet& packet) { handleCancelItemEffect(player, packet); };
    m_packetHandlers[RecvOps::k_USE_SUMMON_BAG]         = [](Player& player, Packet& packet) { handleUseSummonBag(player, packet); };
    m_packetHandlers[RecvOps::k_USE_MOUNT_FOOD]         = [](Player& player, Packet& packet) { handleUseMountFood(player, packet); };
    m_packetHandlers[RecvOps::k_USE_CASH_ITEM]          = [](Player& player, Packet& packet) { handleUseCashItem(player, packet); };
    m_packetHandlers[RecvOps::k_USE_CATCH_ITEM]         = [](Player& player, Packet& packet) { handleUseCatchItem(player, packet); };
    m_packetHandlers[RecvOps::k_USE_SKILL_BOOK]         = [](Player& player, Packet& packet) { handleUseSkillBook(player, packet); };
    m_packetHandlers[RecvOps::k_USE_RETURN_SCROLL]      = [](Player& player, Packet& packet) { handleUseReturnScroll(player, packet); };
    m_packetHandlers[RecvOps::k_USE_UPGRADE_SCROLL]     = [](Player& player, Packet& packet) { handleUseUpgradeScroll(player, packet); };
    m_packetHandlers[RecvOps::k_DISTRIBUTE_AP]          = [](Player& player, Packet& packet) { handleDistributeAP(player, packet); };
    m_packetHandlers[RecvOps::k_HEAL_OVER_TIME]         = [](Player& player, Packet& packet) { handleHealOverTime(player, packet); };
    m_packetHandlers[RecvOps::k_DISTRIBUTE_SP]          = [](Player& player, Packet& packet) { handleDistributeSP(player, packet); };
    m_packetHandlers[RecvOps::k_SPECIAL_MOVE]           = [](Player& player, Packet& packet) { handleSpecialMove(player, packet); };
    m_packetHandlers[RecvOps::k_CANCEL_BUFF]            = [](Player& player, Packet& packet) { handleCancelBuff(player, packet); };
    m_packetHandlers[RecvOps::k_SKILL_EFFECT]           = [](Player& player, Packet& packet) { handleSkillEffect(player, packet); };
    m_packetHandlers[RecvOps::k_MESO_DROP]              = [](Player& player, Packet& packet) { handleMesoDrop(player, packet); };
    m_packetHandlers[RecvOps::k_GIVE_FAME]              = [](Player& player, Packet& packet) { handleGiveFame(player, packet); };
    m_packetHandlers[RecvOps::k_CHAR_INFO_REQUEST]      = [](Player& player, Packet& packet) { handleCharInfoRequest(player, packet); };
    m_packetHandlers[RecvOps::k_CANCEL_DEBUFF]          = [](Player& player, Packet& packet) { handleCancelDebuff(player, packet); };
    m_packetHandlers[RecvOps::k_CHANGE_MAP_SPECIAL]     = [](Player& player, Packet& packet) { handleChangeMapSpecial(player, packet); };
    m_packetHandlers[RecvOps::k_USE_INNER_PORTAL]       = [](Player& player, Packet& packet) { handleUseInnerPortal(player, packet); };
    m_packetHandlers[RecvOps::k_VIP_ADD_MAP]            = [](Player& player, Packet& packet) { handleVipAddMap(player, packet); };
    m_packetHandlers[RecvOps::k_QUEST_ACTION]           = [](Player& player, Packet& packet) { handleQuestAction(player, packet); };
    m_packetHandlers[RecvOps::k_SKILL_MACRO]            = [](Player& player, Packet& packet) { handleSkillMacro(player, packet); };
    m_packetHandlers[RecvOps::k_REPORT_PLAYER]          = [](Player& player, Packet& packet) { handleReportPlayer(player, packet); };
    m_packetHandlers[RecvOps::k_PARTY_CHAT]             = [](Player& player, Packet& packet) { handlePartyChat(player, packet); };
    m_packetHandlers[RecvOps::k_WHISPER]                = [](Player& player, Packet& packet) { handleWhisper(player, packet); };
    m_packetHandlers[RecvOps::k_SPOUSE_CHAT]            = [](Player& player, Packet& packet) { handleSpouseChat(player, packet); };
    m_packetHandlers[RecvOps::k_MESSENGER]              = [](Player& player, Packet& packet) { handleMessenger(player, packet); };
    m_packetHandlers[RecvOps::k_PLAYER_SHOP]            = [](Player& player, Packet& packet) { handlePlayerShop(player, packet); };
    m_packetHandlers[RecvOps::k_PLAYER_INTERACTION]     = [](Player& player, Packet& packet) { handlePlayerInteraction(player, packet); };
    m_packetHandlers[RecvOps::k_PARTY_OPERATION]        = [](Player& player, Packet& packet) { handlePartyOperation(player, packet); };
    m_packetHandlers[RecvOps::k_DENY_PARTY_REQUEST]     = [](Player& player, Packet& packet) { handleDenyPartyRequest(player, packet); };
    m_packetHandlers[RecvOps::k_GUILD_OPERATION]        = [](Player& player, Packet& packet) { handleGuildOperation(player, packet); };
    m_packetHandlers[RecvOps::k_DENY_GUILD_REQUEST]     = [](Player& player, Packet& packet) { handleDenyGuildRequest(player, packet); };
    m_packetHandlers[RecvOps::k_BUDDY_LIST_MODIFY]      = [](Player& player, Packet& packet) { handleBuddyListModify(player, packet); };
    m_packetHandlers[RecvOps::k_NOTE_ACTION]            = [](Player& player, Packet& packet) { handleNoteAction(player, packet); };
    m_packetHandlers[RecvOps::k_USE_DOOR]               = [](Player& player, Packet& packet) { handleUseDoor(player, packet); };
    m_packetHandlers[RecvOps::k_CHANGE_KEY_MAP]         = [](Player& player, Packet& packet) { handleChangeKeymap(player, packet); };
    m_packetHandlers[RecvOps::k_RING_ACTION]            = [](Player& player, Packet& packet) { handleRingAction(player, packet); };
    m_packetHandlers[RecvOps::k_ALLIANCE_OPERATION]     = [](Player& player, Packet& packet) { handleAllianceOperation(player, packet); };
    m_packetHandlers[RecvOps::k_BBS_OPERATION]          = [](Player& player, Packet& packet) { handleBbsOperation(player, packet); };
    m_packetHandlers[RecvOps::k_ENTER_MTS]              = [](Player& player, Packet& packet) { handleEnterMTS(player, packet); };
    m_packetHandlers[RecvOps::k_PET_TALK]               = [](Player& player, Packet& packet) { handlePetTalk(player, packet); };
    m_packetHandlers[RecvOps::k_USE_SOLOMAN_ITEM]       = [](Player& player, Packet& packet) { handleUseSolomanItem(player, packet); };
    m_packetHandlers[RecvOps::k_PET_AUTO_POT]           = [](Player& player, Packet& packet) { handlePetAutoPot(player, packet); };
    m_packetHandlers[RecvOps::k_MOVE_SUMMON]            = [](Player& player, Packet& packet) { handleMoveSummon(player, packet); };
    m_packetHandlers[RecvOps::k_SUMMON_ATTACK]          = [](Player& player, Packet& packet) { handleSummonAttack(player, packet); };
    m_packetHandlers[RecvOps::k_DAMAGE_SUMMON]          = [](Player& player, Packet& packet) { handleDamageSummon(player, packet); };
    m_packetHandlers[RecvOps::k_MOVE_LIFE]              = [](Player& player, Packet& packet) { handleMoveLife(player, packet); };
    m_packetHandlers[RecvOps::k_AUTO_AGGRO]             = [](Player& player, Packet& packet) { handleAutoAggro(player, packet); };
    m_packetHandlers[RecvOps::k_MOB_DAMAGE_MOB]         = [](Player& player, Packet& packet) { handleMobDamageMob(player, packet); };
    m_packetHandlers[RecvOps::k_MONSTER_BOMB]           = [](Player& player, Packet& packet) { handleMonsterBomb(player, packet); };
    m_packetHandlers[RecvOps::k_NPC_ACTION]             = [](Player& player, Packet& packet) { handleNpcAction(player, packet); };
    m_packetHandlers[RecvOps::k_ITEM_PICKUP]            = [](Player& player, Packet& packet) { handleItemPickup(player, packet); };
    m_packetHandlers[RecvOps::k_DAMAGE_REACTOR]         = [](Player& player, Packet& packet) { handleDamageReactor(player, packet); };
    m_packetHandlers[RecvOps::k_MONSTER_CARNIVAL]       = [](Player& player, Packet& packet) { handleMonsterCarnival(player, packet); };
    m_packetHandlers[RecvOps::k_PARTY_SEARCH_REGISTER]  = [](Player& player, Packet& packet) { handlePartySearchRegister(player, packet); };
    m_packetHandlers[RecvOps::k_PARTY_SEARCH_START]     = [](Player& player, Packet& packet) { handlePartySearchStart(player, packet); };
    m_packetHandlers[RecvOps::k_PLAYER_UPDATE]          = [](Player& player, Packet& packet) { handlePlayerUpdate(player, packet); };
    m_packetHandlers[RecvOps::k_MAPLE_TV]               = [](Player& player, Packet& packet) { handleMapleTV(player, packet); };
    m_packetHandlers[RecvOps::k_MTS_OPERATION]          = [](Player& player, Packet& packet) { handleMTSOperation(player, packet); };
    m_packetHandlers[RecvOps::k_TOUCHING_CS]            = [](Player& player, Packet& packet) { handleTouchingCS(player, packet); };
    m_packetHandlers[RecvOps::k_BUY_CS_ITEM]            = [](Player& player, Packet& packet) { handleBuyCSItem(player, packet); };
    m_packetHandlers[RecvOps::k_COUPON_CODE]            = [](Player& player, Packet& packet) { handleCouponCode(player, packet); };
    m_packetHandlers[RecvOps::k_PET_SPAWN]              = [](Player& player, Packet& packet) { handlePetSpawn(player, packet); };
    m_packetHandlers[RecvOps::k_PET_MOVE]               = [](Player& player, Packet& packet) { handlePetMove(player, packet); };
    m_packetHandlers[RecvOps::k_PET_CHAT]               = [](Player& player, Packet& packet) { handlePetChat(player, packet); };
    m_packetHandlers[RecvOps::k_PET_COMMAND]            = [](Player& player, Packet& packet) { handlePetCommand(player, packet); };
    m_packetHandlers[RecvOps::k_PET_LOOT]               = [](Player& player, Packet& packet) { handlePetLoot(player, packet); };
    m_packetHandlers[RecvOps::k_PET_FOOD]               = [](Player& player, Packet& packet) { handlePetFood(player, packet); };
}

// CHANNEL
void PacketHandler::handlePlayerLoggedIn(Player& player, Packet& packet) {}
void PacketHandler::handleStrangeData(Player& player, Packet& packet) {}
void PacketHandler::handleChangeMap(Player& player, Packet& packet) {}
void PacketHandler::handleChangeChannel(Player& player, Packet& packet) {}
void PacketHandler::handleEnterCashShop(Player& player, Packet& packet) {}
void PacketHandler::handleMovePlayer(Player& player, Packet& packet) {}
void PacketHandler::handleCancelChair(Player& player, Packet& packet) {}
void PacketHandler::handleUseChair(Player& player, Packet& packet) {}
void PacketHandler::handleCloseRangeAttack(Player& player, Packet& packet) {}
void PacketHandler::handleRangedAttack(Player& player, Packet& packet) {}
void PacketHandler::handleMagicAttack(Player& player, Packet& packet) {}
void PacketHandler::handleEnergyOrbAttack(Player& player, Packet& packet) {}
void PacketHandler::handleTakeDamage(Player& player, Packet& packet) {}
void PacketHandler::handleGeneralChat(Player& player, Packet& packet) {}
void PacketHandler::handleCloseChalkboard(Player& player, Packet& packet) {}
void PacketHandler::handleFaceExpression(Player& player, Packet& packet) {}
void PacketHandler::handleUseItemEffect(Player& player, Packet& packet) {}
void PacketHandler::handleNpcTalk(Player& player, Packet& packet) {}
void PacketHandler::handleNpcTalkMore(Player& player, Packet& packet) {}
void PacketHandler::handleNpcShop(Player& player, Packet& packet) {}
void PacketHandler::handleStorage(Player& player, Packet& packet) {}
void PacketHandler::handleHiredMerchantRequest(Player& player, Packet& packet) {}
void PacketHandler::handleDueyAction(Player& player, Packet& packet) {}
void PacketHandler::handleItemSort(Player& player, Packet& packet) {}
void PacketHandler::handleItemSort2(Player& player, Packet& packet) {}
void PacketHandler::handleItemMove(Player& player, Packet& packet) {}
void PacketHandler::handleUseItem(Player& player, Packet& packet) {}
void PacketHandler::handleCancelItemEffect(Player& player, Packet& packet) {}
void PacketHandler::handleUseSummonBag(Player& player, Packet& packet) {}
void PacketHandler::handleUseMountFood(Player& player, Packet& packet) {}
void PacketHandler::handleUseCashItem(Player& player, Packet& packet) {}
void PacketHandler::handleUseCatchItem(Player& player, Packet& packet) {}
void PacketHandler::handleUseSkillBook(Player& player, Packet& packet) {}
void PacketHandler::handleUseReturnScroll(Player& player, Packet& packet) {}
void PacketHandler::handleUseUpgradeScroll(Player& player, Packet& packet) {}
void PacketHandler::handleDistributeAP(Player& player, Packet& packet) {}
void PacketHandler::handleHealOverTime(Player& player, Packet& packet) {}
void PacketHandler::handleDistributeSP(Player& player, Packet& packet) {}
void PacketHandler::handleSpecialMove(Player& player, Packet& packet) {}
void PacketHandler::handleCancelBuff(Player& player, Packet& packet) {}
void PacketHandler::handleSkillEffect(Player& player, Packet& packet) {}
void PacketHandler::handleMesoDrop(Player& player, Packet& packet) {}
void PacketHandler::handleGiveFame(Player& player, Packet& packet) {}
void PacketHandler::handleCharInfoRequest(Player& player, Packet& packet) {}
void PacketHandler::handleCancelDebuff(Player& player, Packet& packet) {}
void PacketHandler::handleChangeMapSpecial(Player& player, Packet& packet) {}
void PacketHandler::handleUseInnerPortal(Player& player, Packet& packet) {}
void PacketHandler::handleVipAddMap(Player& player, Packet& packet) {}
void PacketHandler::handleQuestAction(Player& player, Packet& packet) {}
void PacketHandler::handleSkillMacro(Player& player, Packet& packet) {}
void PacketHandler::handleReportPlayer(Player& player, Packet& packet) {}
void PacketHandler::handlePartyChat(Player& player, Packet& packet) {}
void PacketHandler::handleWhisper(Player& player, Packet& packet) {}
void PacketHandler::handleSpouseChat(Player& player, Packet& packet) {}
void PacketHandler::handleMessenger(Player& player, Packet& packet) {}
void PacketHandler::handlePlayerShop(Player& player, Packet& packet) {}
void PacketHandler::handlePlayerInteraction(Player& player, Packet& packet) {}
void PacketHandler::handlePartyOperation(Player& player, Packet& packet) {}
void PacketHandler::handleDenyPartyRequest(Player& player, Packet& packet) {}
void PacketHandler::handleGuildOperation(Player& player, Packet& packet) {}
void PacketHandler::handleDenyGuildRequest(Player& player, Packet& packet) {}
void PacketHandler::handleBuddyListModify(Player& player, Packet& packet) {}
void PacketHandler::handleNoteAction(Player& player, Packet& packet) {}
void PacketHandler::handleUseDoor(Player& player, Packet& packet) {}
void PacketHandler::handleChangeKeymap(Player& player, Packet& packet) {}
void PacketHandler::handleRingAction(Player& player, Packet& packet) {}
void PacketHandler::handleAllianceOperation(Player& player, Packet& packet) {}
void PacketHandler::handleBbsOperation(Player& player, Packet& packet) {}
void PacketHandler::handleEnterMTS(Player& player, Packet& packet) {}
void PacketHandler::handlePetTalk(Player& player, Packet& packet) {}
void PacketHandler::handleUseSolomanItem(Player& player, Packet& packet) {}
void PacketHandler::handlePetAutoPot(Player& player, Packet& packet) {}
void PacketHandler::handleMoveSummon(Player& player, Packet& packet) {}
void PacketHandler::handleSummonAttack(Player& player, Packet& packet) {}
void PacketHandler::handleDamageSummon(Player& player, Packet& packet) {}
void PacketHandler::handleMoveLife(Player& player, Packet& packet) {}
void PacketHandler::handleAutoAggro(Player& player, Packet& packet) {}
void PacketHandler::handleMobDamageMob(Player& player, Packet& packet) {}
void PacketHandler::handleMonsterBomb(Player& player, Packet& packet) {}
void PacketHandler::handleNpcAction(Player& player, Packet& packet) {}
void PacketHandler::handleItemPickup(Player& player, Packet& packet) {}
void PacketHandler::handleDamageReactor(Player& player, Packet& packet) {}
void PacketHandler::handleMonsterCarnival(Player& player, Packet& packet) {}
void PacketHandler::handlePartySearchRegister(Player& player, Packet& packet) {}
void PacketHandler::handlePartySearchStart(Player& player, Packet& packet) {}
void PacketHandler::handlePlayerUpdate(Player& player, Packet& packet) {}
void PacketHandler::handleMapleTV(Player& player, Packet& packet) {}
void PacketHandler::handleMTSOperation(Player& player, Packet& packet) {}
void PacketHandler::handleTouchingCS(Player& player, Packet& packet) {}
void PacketHandler::handleBuyCSItem(Player& player, Packet& packet) {}
void PacketHandler::handleCouponCode(Player& player, Packet& packet) {}
void PacketHandler::handlePetSpawn(Player& player, Packet& packet) {}
void PacketHandler::handlePetMove(Player& player, Packet& packet) {}
void PacketHandler::handlePetChat(Player& player, Packet& packet) {}
void PacketHandler::handlePetCommand(Player& player, Packet& packet) {}
void PacketHandler::handlePetLoot(Player& player, Packet& packet) {}
void PacketHandler::handlePetFood(Player& player, Packet& packet) {}