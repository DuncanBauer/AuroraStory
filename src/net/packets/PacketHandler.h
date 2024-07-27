#pragma once

#include "Typedefs.h"

class PacketHandler
{
public:
    PacketHandler() = delete;

    static void registerHandlers();

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
    static void handlePlayerLoggedIn(Player& player, Packet& packet);
    static void handleStrangeData(Player& player, Packet& packet);
    static void handleChangeMap(Player& player, Packet& packet);
    static void handleChangeChannel(Player& player, Packet& packet);
    static void handleEnterCashShop(Player& player, Packet& packet);
    static void handleMovePlayer(Player& player, Packet& packet);
    static void handleCancelChair(Player& player, Packet& packet);
    static void handleUseChair(Player& player, Packet& packet);
    static void handleCloseRangeAttack(Player& player, Packet& packet);
    static void handleRangedAttack(Player& player, Packet& packet);
    static void handleMagicAttack(Player& player, Packet& packet);
    static void handleEnergyOrbAttack(Player& player, Packet& packet);
    static void handleTakeDamage(Player& player, Packet& packet);
    static void handleGeneralChat(Player& player, Packet& packet);
    static void handleCloseChalkboard(Player& player, Packet& packet);
    static void handleFaceExpression(Player& player, Packet& packet);
    static void handleUseItemEffect(Player& player, Packet& packet);
    static void handleNpcTalk(Player& player, Packet& packet);
    static void handleNpcTalkMore(Player& player, Packet& packet);
    static void handleNpcShop(Player& player, Packet& packet);
    static void handleStorage(Player& player, Packet& packet);
    static void handleHiredMerchantRequest(Player& player, Packet& packet);
    static void handleDueyAction(Player& player, Packet& packet);
    static void handleItemSort(Player& player, Packet& packet);
    static void handleItemSort2(Player& player, Packet& packet);
    static void handleItemMove(Player& player, Packet& packet);
    static void handleUseItem(Player& player, Packet& packet);
    static void handleCancelItemEffect(Player& player, Packet& packet);
    static void handleUseSummonBag(Player& player, Packet& packet);
    static void handleUseMountFood(Player& player, Packet& packet);
    static void handleUseCashItem(Player& player, Packet& packet);
    static void handleUseCatchItem(Player& player, Packet& packet);
    static void handleUseSkillBook(Player& player, Packet& packet);
    static void handleUseReturnScroll(Player& player, Packet& packet);
    static void handleUseUpgradeScroll(Player& player, Packet& packet);
    static void handleDistributeAP(Player& player, Packet& packet);
    static void handleHealOverTime(Player& player, Packet& packet);
    static void handleDistributeSP(Player& player, Packet& packet);
    static void handleSpecialMove(Player& player, Packet& packet);
    static void handleCancelBuff(Player& player, Packet& packet);
    static void handleSkillEffect(Player& player, Packet& packet);
    static void handleMesoDrop(Player& player, Packet& packet);
    static void handleGiveFame(Player& player, Packet& packet);
    static void handleCharInfoRequest(Player& player, Packet& packet);
    static void handleCancelDebuff(Player& player, Packet& packet);
    static void handleChangeMapSpecial(Player& player, Packet& packet);
    static void handleUseInnerPortal(Player& player, Packet& packet);
    static void handleVipAddMap(Player& player, Packet& packet);
    static void handleQuestAction(Player& player, Packet& packet);
    static void handleSkillMacro(Player& player, Packet& packet);
    static void handleReportPlayer(Player& player, Packet& packet);
    static void handlePartyChat(Player& player, Packet& packet);
    static void handleWhisper(Player& player, Packet& packet);
    static void handleSpouseChat(Player& player, Packet& packet);
    static void handleMessenger(Player& player, Packet& packet);
    static void handlePlayerShop(Player& player, Packet& packet);
    static void handlePlayerInteraction(Player& player, Packet& packet);
    static void handlePartyOperation(Player& player, Packet& packet);
    static void handleDenyPartyRequest(Player& player, Packet& packet);
    static void handleGuildOperation(Player& player, Packet& packet);
    static void handleDenyGuildRequest(Player& player, Packet& packet);
    static void handleBuddyListModify(Player& player, Packet& packet);
    static void handleNoteAction(Player& player, Packet& packet);
    static void handleUseDoor(Player& player, Packet& packet);
    static void handleChangeKeymap(Player& player, Packet& packet);
    static void handleRingAction(Player& player, Packet& packet);
    static void handleAllianceOperation(Player& player, Packet& packet);
    static void handleBbsOperation(Player& player, Packet& packet);
    static void handleEnterMTS(Player& player, Packet& packet);
    static void handlePetTalk(Player& player, Packet& packet);
    static void handleUseSolomanItem(Player& player, Packet& packet);
    static void handlePetAutoPot(Player& player, Packet& packet);
    static void handleMoveSummon(Player& player, Packet& packet);
    static void handleSummonAttack(Player& player, Packet& packet);
    static void handleDamageSummon(Player& player, Packet& packet);
    static void handleMoveLife(Player& player, Packet& packet);
    static void handleAutoAggro(Player& player, Packet& packet);
    static void handleMobDamageMob(Player& player, Packet& packet);
    static void handleMonsterBomb(Player& player, Packet& packet);
    static void handleNpcAction(Player& player, Packet& packet);
    static void handleItemPickup(Player& player, Packet& packet);
    static void handleDamageReactor(Player& player, Packet& packet);
    static void handleMonsterCarnival(Player& player, Packet& packet);
    static void handlePartySearchRegister(Player& player, Packet& packet);
    static void handlePartySearchStart(Player& player, Packet& packet);
    static void handlePlayerUpdate(Player& player, Packet& packet);
    static void handleMapleTV(Player& player, Packet& packet);
    static void handleMTSOperation(Player& player, Packet& packet);
    static void handleTouchingCS(Player& player, Packet& packet);
    static void handleBuyCSItem(Player& player, Packet& packet);
    static void handleCouponCode(Player& player, Packet& packet);
    static void handlePetSpawn(Player& player, Packet& packet);
    static void handlePetMove(Player& player, Packet& packet);
    static void handlePetChat(Player& player, Packet& packet);
    static void handlePetCommand(Player& player, Packet& packet);
    static void handlePetLoot(Player& player, Packet& packet);
    static void handlePetFood(Player& player, Packet& packet);

public:
    static PacketHandlers m_packetHandlers;
};