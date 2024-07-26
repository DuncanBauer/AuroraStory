#include "pch.h"

#include "PacketHandler.h"

#include "constants/PacketConstant.h"

namespace net
{
    PacketHandlers PacketHandler::m_packetHandlers;

    void PacketHandler::registerHandlers()
    {
        // GENERAL
        m_packetHandlers[constant::RecvOps::k_PONG] = [this](net::Packet& packet) { handlePong(packet); };

        // LOGIN
        m_packetHandlers[constant::RecvOps::k_LOGIN_PASSWORD]         = [this](net::Packet& packet) { handleLoginPassword(packet); };
        m_packetHandlers[constant::RecvOps::k_GUEST_LOGIN]            = [this](net::Packet& packet) { handleGuestLogin(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVER_LIST_REREQUEST]  = [this](net::Packet& packet) { handleServerListRerequest(packet); };
        m_packetHandlers[constant::RecvOps::k_CHAR_LIST_REQUEST]      = [this](net::Packet& packet) { handleCharListRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVER_STATUS_REQUEST]  = [this](net::Packet& packet) { handleServerStatusRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_SET_GENDER]             = [this](net::Packet& packet) { handleSetGender(packet); };
        m_packetHandlers[constant::RecvOps::k_AFTER_LOGIN]            = [this](net::Packet& packet) { handleAfterLogin(packet); };
        m_packetHandlers[constant::RecvOps::k_REGISTER_PIN]           = [this](net::Packet& packet) { handleRegisterPin(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVER_LIST_REQUEST]    = [this](net::Packet& packet) { handleServerListRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_PLAYER_DC]              = [this](net::Packet& packet) { handlePlayerDC(packet); };
        m_packetHandlers[constant::RecvOps::k_VIEW_ALL_CHAR]          = [this](net::Packet& packet) { handleViewAllChar(packet); };
        m_packetHandlers[constant::RecvOps::k_PICK_ALL_CHAR]          = [this](net::Packet& packet) { handlePickAllChar(packet); };
        m_packetHandlers[constant::RecvOps::k_CHAR_SELECT]            = [this](net::Packet& packet) { handleCharSelect(packet); };
        m_packetHandlers[constant::RecvOps::k_CHECK_CHAR_NAME]        = [this](net::Packet& packet) { handleCheckCharName(packet); };
        m_packetHandlers[constant::RecvOps::k_CREATE_CHAR]            = [this](net::Packet& packet) { handleCreateChar(packet); };
        m_packetHandlers[constant::RecvOps::k_DELETE_CHAR]            = [this](net::Packet& packet) { handleDeleteChar(packet); };
        m_packetHandlers[constant::RecvOps::k_CLIENT_START]           = [this](net::Packet& packet) { handleClientStart(packet); };
        m_packetHandlers[constant::RecvOps::k_RELOG]                  = [this](net::Packet& packet) { handleRelog(packet); };

        // CHANNEL
        m_packetHandlers[constant::RecvOps::k_PLAYER_LOGGED_IN]       = [this](net::Packet& packet) { handlePlayerLoggedIn(packet); };
        m_packetHandlers[constant::RecvOps::k_STRANGE_DATA]           = [this](net::Packet& packet) { handleStrangeData(packet); };
        m_packetHandlers[constant::RecvOps::k_CHANGE_MAP]             = [this](net::Packet& packet) { handleChangeMap(packet); };
        m_packetHandlers[constant::RecvOps::k_CHANGE_CHANNEL]         = [this](net::Packet& packet) { handleChangeChannel(packet); };
        m_packetHandlers[constant::RecvOps::k_ENTER_CASH_SHOP]        = [this](net::Packet& packet) { handleEnterCashShop(packet); };
        m_packetHandlers[constant::RecvOps::k_MOVE_PLAYER]            = [this](net::Packet& packet) { handleMovePlayer(packet); };
        m_packetHandlers[constant::RecvOps::k_CANCEL_CHAIR]           = [this](net::Packet& packet) { handleCancelChair(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_CHAIR]              = [this](net::Packet& packet) { handleUseChair(packet); };
        m_packetHandlers[constant::RecvOps::k_CLOSE_RANGE_ATTACK]     = [this](net::Packet& packet) { handleCloseRangeAttack(packet); };
        m_packetHandlers[constant::RecvOps::k_RANGED_ATTACK]          = [this](net::Packet& packet) { handleRangedAttack(packet); };
        m_packetHandlers[constant::RecvOps::k_MAGIC_ATTACK]           = [this](net::Packet& packet) { handleMagicAttack(packet); };
        m_packetHandlers[constant::RecvOps::k_ENERGY_ORB_ATTACK]      = [this](net::Packet& packet) { handleEnergyOrbAttack(packet); };
        m_packetHandlers[constant::RecvOps::k_TAKE_DAMAGE]            = [this](net::Packet& packet) { handleTakeDamage(packet); };
        m_packetHandlers[constant::RecvOps::k_GENERAL_CHAT]           = [this](net::Packet& packet) { handleGeneralChat(packet); };
        m_packetHandlers[constant::RecvOps::k_CLOSE_CHALKBOARD]       = [this](net::Packet& packet) { handleCloseChalkboard(packet); };
        m_packetHandlers[constant::RecvOps::k_FACE_EXPRESSION]        = [this](net::Packet& packet) { handleFaceExpression(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_ITEM_EFFECT]        = [this](net::Packet& packet) { handleUseItemEffect(packet); };
        m_packetHandlers[constant::RecvOps::k_NPC_TALK]               = [this](net::Packet& packet) { handleNpcTalk(packet); };
        m_packetHandlers[constant::RecvOps::k_NPC_TALK_MORE]          = [this](net::Packet& packet) { handleNpcTalkMore(packet); };
        m_packetHandlers[constant::RecvOps::k_NPC_SHOP]               = [this](net::Packet& packet) { handleNpcShop(packet); };
        m_packetHandlers[constant::RecvOps::k_STORAGE]                = [this](net::Packet& packet) { handleStorage(packet); };
        m_packetHandlers[constant::RecvOps::k_HIRED_MERCHANT_REQUEST] = [this](net::Packet& packet) { handleHiredMerchantRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_DUEY_ACTION]            = [this](net::Packet& packet) { handleDueyAction(packet); };
        m_packetHandlers[constant::RecvOps::k_ITEM_SORT]              = [this](net::Packet& packet) { handleItemSort(packet); };
        m_packetHandlers[constant::RecvOps::k_ITEM_SORT2]             = [this](net::Packet& packet) { handleItemSort2(packet); };
        m_packetHandlers[constant::RecvOps::k_ITEM_MOVE]              = [this](net::Packet& packet) { handleItemMove(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_ITEM]               = [this](net::Packet& packet) { handleUseItem(packet); };
        m_packetHandlers[constant::RecvOps::k_CANCEL_ITEM_EFFECT]     = [this](net::Packet& packet) { handleCancelItemEffect(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_SUMMON_BAG]         = [this](net::Packet& packet) { handleUseSummonBag(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_MOUNT_FOOD]         = [this](net::Packet& packet) { handleUseMountFood(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_CASH_ITEM]          = [this](net::Packet& packet) { handleUseCashItem(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_CATCH_ITEM]         = [this](net::Packet& packet) { handleUseCatchItem(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_SKILL_BOOK]         = [this](net::Packet& packet) { handleUseSkillBook(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_RETURN_SCROLL]      = [this](net::Packet& packet) { handleUseReturnScroll(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_UPGRADE_SCROLL]     = [this](net::Packet& packet) { handleUseUpgradeScroll(packet); };
        m_packetHandlers[constant::RecvOps::k_DISTRIBUTE_AP]          = [this](net::Packet& packet) { handleDistributeAP(packet); };
        m_packetHandlers[constant::RecvOps::k_HEAL_OVER_TIME]         = [this](net::Packet& packet) { handleHealOverTime(packet); };
        m_packetHandlers[constant::RecvOps::k_DISTRIBUTE_SP]          = [this](net::Packet& packet) { handleDistributeSP(packet); };
        m_packetHandlers[constant::RecvOps::k_SPECIAL_MOVE]           = [this](net::Packet& packet) { handleSpecialMove(packet); };
        m_packetHandlers[constant::RecvOps::k_CANCEL_BUFF]            = [this](net::Packet& packet) { handleCancelBuff(packet); };
        m_packetHandlers[constant::RecvOps::k_SKILL_EFFECT]           = [this](net::Packet& packet) { handleSkillEffect(packet); };
        m_packetHandlers[constant::RecvOps::k_MESO_DROP]              = [this](net::Packet& packet) { handleMesoDrop(packet); };
        m_packetHandlers[constant::RecvOps::k_GIVE_FAME]              = [this](net::Packet& packet) { handleGiveFame(packet); };
        m_packetHandlers[constant::RecvOps::k_CHAR_INFO_REQUEST]      = [this](net::Packet& packet) { handleCharInfoRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_CANCEL_DEBUFF]          = [this](net::Packet& packet) { handleCancelDebuff(packet); };
        m_packetHandlers[constant::RecvOps::k_CHANGE_MAP_SPECIAL]     = [this](net::Packet& packet) { handleChangeMapSpecial(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_INNER_PORTAL]       = [this](net::Packet& packet) { handleUseInnerPortal(packet); };
        m_packetHandlers[constant::RecvOps::k_VIP_ADD_MAP]            = [this](net::Packet& packet) { handleVipAddMap(packet); };
        m_packetHandlers[constant::RecvOps::k_QUEST_ACTION]           = [this](net::Packet& packet) { handleQuestAction(packet); };
        m_packetHandlers[constant::RecvOps::k_SKILL_MACRO]            = [this](net::Packet& packet) { handleSkillMacro(packet); };
        m_packetHandlers[constant::RecvOps::k_REPORT_PLAYER]          = [this](net::Packet& packet) { handleReportPlayer(packet); };
        m_packetHandlers[constant::RecvOps::k_PARTY_CHAT]             = [this](net::Packet& packet) { handlePartyChat(packet); };
        m_packetHandlers[constant::RecvOps::k_WHISPER]                = [this](net::Packet& packet) { handleWhisper(packet); };
        m_packetHandlers[constant::RecvOps::k_SPOUSE_CHAT]            = [this](net::Packet& packet) { handleSpouseChat(packet); };
        m_packetHandlers[constant::RecvOps::k_MESSENGER]              = [this](net::Packet& packet) { handleMessenger(packet); };
        m_packetHandlers[constant::RecvOps::k_PLAYER_SHOP]            = [this](net::Packet& packet) { handlePlayerShop(packet); };
        m_packetHandlers[constant::RecvOps::k_PLAYER_INTERACTION]     = [this](net::Packet& packet) { handlePlayerInteraction(packet); };
        m_packetHandlers[constant::RecvOps::k_PARTY_OPERATION]        = [this](net::Packet& packet) { handlePartyOperation(packet); };
        m_packetHandlers[constant::RecvOps::k_DENY_PARTY_REQUEST]     = [this](net::Packet& packet) { handleDenyPartyRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_GUILD_OPERATION]        = [this](net::Packet& packet) { handleGuildOperation(packet); };
        m_packetHandlers[constant::RecvOps::k_DENY_GUILD_REQUEST]     = [this](net::Packet& packet) { handleDenyGuildRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_BUDDY_LIST_MODIFY]      = [this](net::Packet& packet) { handleBuddyListModify(packet); };
        m_packetHandlers[constant::RecvOps::k_NOTE_ACTION]            = [this](net::Packet& packet) { handleNoteAction(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_DOOR]               = [this](net::Packet& packet) { handleUseDoor(packet); };
        m_packetHandlers[constant::RecvOps::k_CHANGE_KEY_MAP]         = [this](net::Packet& packet) { handleChangeKeymap(packet); };
        m_packetHandlers[constant::RecvOps::k_RING_ACTION]            = [this](net::Packet& packet) { handleRingAction(packet); };
        m_packetHandlers[constant::RecvOps::k_ALLIANCE_OPERATION]     = [this](net::Packet& packet) { handleAllianceOperation(packet); };
        m_packetHandlers[constant::RecvOps::k_BBS_OPERATION]          = [this](net::Packet& packet) { handleBbsOperation(packet); };
        m_packetHandlers[constant::RecvOps::k_ENTER_MTS]              = [this](net::Packet& packet) { handleEnterMTS(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_TALK]               = [this](net::Packet& packet) { handlePetTalk(packet); };
        m_packetHandlers[constant::RecvOps::k_USE_SOLOMAN_ITEM]       = [this](net::Packet& packet) { handleUseSolomanItem(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_AUTO_POT]           = [this](net::Packet& packet) { handlePetAutoPot(packet); };
        m_packetHandlers[constant::RecvOps::k_MOVE_SUMMON]            = [this](net::Packet& packet) { handleMoveSummon(packet); };
        m_packetHandlers[constant::RecvOps::k_SUMMON_ATTACK]          = [this](net::Packet& packet) { handleSummonAttack(packet); };
        m_packetHandlers[constant::RecvOps::k_DAMAGE_SUMMON]          = [this](net::Packet& packet) { handleDamageSummon(packet); };
        m_packetHandlers[constant::RecvOps::k_MOVE_LIFE]              = [this](net::Packet& packet) { handleMoveLife(packet); };
        m_packetHandlers[constant::RecvOps::k_AUTO_AGGRO]             = [this](net::Packet& packet) { handleAutoAggro(packet); };
        m_packetHandlers[constant::RecvOps::k_MOB_DAMAGE_MOB]         = [this](net::Packet& packet) { handleMobDamageMob(packet); };
        m_packetHandlers[constant::RecvOps::k_MONSTER_BOMB]           = [this](net::Packet& packet) { handleMonsterBomb(packet); };
        m_packetHandlers[constant::RecvOps::k_NPC_ACTION]             = [this](net::Packet& packet) { handleNpcAction(packet); };
        m_packetHandlers[constant::RecvOps::k_ITEM_PICKUP]            = [this](net::Packet& packet) { handleItemPickup(packet); };
        m_packetHandlers[constant::RecvOps::k_DAMAGE_REACTOR]         = [this](net::Packet& packet) { handleDamageReactor(packet); };
        m_packetHandlers[constant::RecvOps::k_MONSTER_CARNIVAL]       = [this](net::Packet& packet) { handleMonsterCarnival(packet); };
        m_packetHandlers[constant::RecvOps::k_PARTY_SEARCH_REGISTER]  = [this](net::Packet& packet) { handlePartySearchRegister(packet); };
        m_packetHandlers[constant::RecvOps::k_PARTY_SEARCH_START]     = [this](net::Packet& packet) { handlePartySearchStart(packet); };
        m_packetHandlers[constant::RecvOps::k_PLAYER_UPDATE]          = [this](net::Packet& packet) { handlePlayerUpdate(packet); };
        m_packetHandlers[constant::RecvOps::k_MAPLE_TV]               = [this](net::Packet& packet) { handleMapleTV(packet); };
        m_packetHandlers[constant::RecvOps::k_MTS_OPERATION]          = [this](net::Packet& packet) { handleMTSOperation(packet); };
        m_packetHandlers[constant::RecvOps::k_TOUCHING_CS]            = [this](net::Packet& packet) { handleTouchingCS(packet); };
        m_packetHandlers[constant::RecvOps::k_BUY_CS_ITEM]            = [this](net::Packet& packet) { handleBuyCSItem(packet); };
        m_packetHandlers[constant::RecvOps::k_COUPON_CODE]            = [this](net::Packet& packet) { handleCouponCode(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_SPAWN]              = [this](net::Packet& packet) { handlePetSpawn(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_MOVE]               = [this](net::Packet& packet) { handlePetMove(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_CHAT]               = [this](net::Packet& packet) { handlePetChat(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_COMMAND]            = [this](net::Packet& packet) { handlePetCommand(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_LOOT]               = [this](net::Packet& packet) { handlePetLoot(packet); };
        m_packetHandlers[constant::RecvOps::k_PET_FOOD]               = [this](net::Packet& packet) { handlePetFood(packet); };
    }

        // CHANNEL
        void PacketHandler::handlePlayerLoggedIn(Packet& packet) {}
        void PacketHandler::handleStrangeData(Packet& packet) {}
        void PacketHandler::handleChangeMap(Packet& packet) {}
        void PacketHandler::handleChangeChannel(Packet& packet) {}
        void PacketHandler::handleEnterCashShop(Packet& packet) {}
        void PacketHandler::handleMovePlayer(Packet& packet) {}
        void PacketHandler::handleCancelChair(Packet& packet) {}
        void PacketHandler::handleUseChair(Packet& packet) {}
        void PacketHandler::handleCloseRangeAttack(Packet& packet) {}
        void PacketHandler::handleRangedAttack(Packet& packet) {}
        void PacketHandler::handleMagicAttack(Packet& packet) {}
        void PacketHandler::handleEnergyOrbAttack(Packet& packet) {}
        void PacketHandler::handleTakeDamage(Packet& packet) {}
        void PacketHandler::handleGeneralChat(Packet& packet) {}
        void PacketHandler::handleCloseChalkboard(Packet& packet) {}
        void PacketHandler::handleFaceExpression(Packet& packet) {}
        void PacketHandler::handleUseItemEffect(Packet& packet) {}
        void PacketHandler::handleNpcTalk(Packet& packet) {}
        void PacketHandler::handleNpcTalkMore(Packet& packet) {}
        void PacketHandler::handleNpcShop(Packet& packet) {}
        void PacketHandler::handleStorage(Packet& packet) {}
        void PacketHandler::handleHiredMerchantRequest(Packet& packet) {}
        void PacketHandler::handleDueyAction(Packet& packet) {}
        void PacketHandler::handleItemSort(Packet& packet) {}
        void PacketHandler::handleItemSort2(Packet& packet) {}
        void PacketHandler::handleItemMove(Packet& packet) {}
        void PacketHandler::handleUseItem(Packet& packet) {}
        void PacketHandler::handleCancelItemEffect(Packet& packet) {}
        void PacketHandler::handleUseSummonBag(Packet& packet) {}
        void PacketHandler::handleUseMountFood(Packet& packet) {}
        void PacketHandler::handleUseCashItem(Packet& packet) {}
        void PacketHandler::handleUseCatchItem(Packet& packet) {}
        void PacketHandler::handleUseSkillBook(Packet& packet) {}
        void PacketHandler::handleUseReturnScroll(Packet& packet) {}
        void PacketHandler::handleUseUpgradeScroll(Packet& packet) {}
        void PacketHandler::handleDistributeAP(Packet& packet) {}
        void PacketHandler::handleHealOverTime(Packet& packet) {}
        void PacketHandler::handleDistributeSP(Packet& packet) {}
        void PacketHandler::handleSpecialMove(Packet& packet) {}
        void PacketHandler::handleCancelBuff(Packet& packet) {}
        void PacketHandler::handleSkillEffect(Packet& packet) {}
        void PacketHandler::handleMesoDrop(Packet& packet) {}
        void PacketHandler::handleGiveFame(Packet& packet) {}
        void PacketHandler::handleCharInfoRequest(Packet& packet) {}
        void PacketHandler::handleCancelDebuff(Packet& packet) {}
        void PacketHandler::handleChangeMapSpecial(Packet& packet) {}
        void PacketHandler::handleUseInnerPortal(Packet& packet) {}
        void PacketHandler::handleVipAddMap(Packet& packet) {}
        void PacketHandler::handleQuestAction(Packet& packet) {}
        void PacketHandler::handleSkillMacro(Packet& packet) {}
        void PacketHandler::handleReportPlayer(Packet& packet) {}
        void PacketHandler::handlePartyChat(Packet& packet) {}
        void PacketHandler::handleWhisper(Packet& packet) {}
        void PacketHandler::handleSpouseChat(Packet& packet) {}
        void PacketHandler::handleMessenger(Packet& packet) {}
        void PacketHandler::handlePlayerShop(Packet& packet) {}
        void PacketHandler::handlePlayerInteraction(Packet& packet) {}
        void PacketHandler::handlePartyOperation(Packet& packet) {}
        void PacketHandler::handleDenyPartyRequest(Packet& packet) {}
        void PacketHandler::handleGuildOperation(Packet& packet) {}
        void PacketHandler::handleDenyGuildRequest(Packet& packet) {}
        void PacketHandler::handleBuddyListModify(Packet& packet) {}
        void PacketHandler::handleNoteAction(Packet& packet) {}
        void PacketHandler::handleUseDoor(Packet& packet) {}
        void PacketHandler::handleChangeKeymap(Packet& packet) {}
        void PacketHandler::handleRingAction(Packet& packet) {}
        void PacketHandler::handleAllianceOperation(Packet& packet) {}
        void PacketHandler::handleBbsOperation(Packet& packet) {}
        void PacketHandler::handleEnterMTS(Packet& packet) {}
        void PacketHandler::handlePetTalk(Packet& packet) {}
        void PacketHandler::handleUseSolomanItem(Packet& packet) {}
        void PacketHandler::handlePetAutoPot(Packet& packet) {}
        void PacketHandler::handleMoveSummon(Packet& packet) {}
        void PacketHandler::handleSummonAttack(Packet& packet) {}
        void PacketHandler::handleDamageSummon(Packet& packet) {}
        void PacketHandler::handleMoveLife(Packet& packet) {}
        void PacketHandler::handleAutoAggro(Packet& packet) {}
        void PacketHandler::handleMobDamageMob(Packet& packet) {}
        void PacketHandler::handleMonsterBomb(Packet& packet) {}
        void PacketHandler::handleNpcAction(Packet& packet) {}
        void PacketHandler::handleItemPickup(Packet& packet) {}
        void PacketHandler::handleDamageReactor(Packet& packet) {}
        void PacketHandler::handleMonsterCarnival(Packet& packet) {}
        void PacketHandler::handlePartySearchRegister(Packet& packet) {}
        void PacketHandler::handlePartySearchStart(Packet& packet) {}
        void PacketHandler::handlePlayerUpdate(Packet& packet) {}
        void PacketHandler::handleMapleTV(Packet& packet) {}
        void PacketHandler::handleMTSOperation(Packet& packet) {}
        void PacketHandler::handleTouchingCS(Packet& packet) {}
        void PacketHandler::handleBuyCSItem(Packet& packet) {}
        void PacketHandler::handleCouponCode(Packet& packet) {}
        void PacketHandler::handlePetSpawn(Packet& packet) {}
        void PacketHandler::handlePetMove(Packet& packet) {}
        void PacketHandler::handlePetChat(Packet& packet) {}
        void PacketHandler::handlePetCommand(Packet& packet) {}
        void PacketHandler::handlePetLoot(Packet& packet) {}
        void PacketHandler::handlePetFood(Packet& packet) {}
}