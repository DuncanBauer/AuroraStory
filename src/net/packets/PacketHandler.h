#pragma once

#include <unordered_map>
#include <functional>

#include "net/asio/TCPNet.h"

namespace net
{
    typedef std::unordered_map<uint16_t, std::function<void(Packet&)>> PacketHandlers;

    class PacketHandler
    {
    public:
        void registerHandlers();

        // GENERAL
        static void handlePong(Packet& packet);

        // LOGIN
        static void handleLoginPassword(Packet& packet);
        static void handleGuestLogin(Packet& packet);
        static void handleServerListRerequest(Packet& packet);
        static void handleCharListRequest(Packet& packet);
        static void handleServerStatusRequest(Packet& packet);
        static void handleSetGender(Packet& packet);
        static void handleAfterLogin(Packet& packet);
        static void handleRegisterPin(Packet& packet);
        static void handleServerListRequest(Packet& packet);
        static void handlePlayerDC(Packet& packet);
        static void handleViewAllChar(Packet& packet);
        static void handlePickAllChar(Packet& packet);
        static void handleCharSelect(Packet& packet);
        static void handleCheckCharName(Packet& packet);
        static void handleCreateChar(Packet& packet);
        static void handleDeleteChar(Packet& packet);
        static void handleClientStart(Packet& packet);
        static void handleRelog(Packet& packet);

        // CHANNEL
        static void handlePlayerLoggedIn(Packet& packet);
        static void handleStrangeData(Packet& packet);
        static void handleChangeMap(Packet& packet);
        static void handleChangeChannel(Packet& packet);
        static void handleEnterCashShop(Packet& packet);
        static void handleMovePlayer(Packet& packet);
        static void handleCancelChair(Packet& packet);
        static void handleUseChair(Packet& packet);
        static void handleCloseRangeAttack(Packet& packet);
        static void handleRangedAttack(Packet& packet);
        static void handleMagicAttack(Packet& packet);
        static void handleEnergyOrbAttack(Packet& packet);
        static void handleTakeDamage(Packet& packet);
        static void handleGeneralChat(Packet& packet);
        static void handleCloseChalkboard(Packet& packet);
        static void handleFaceExpression(Packet& packet);
        static void handleUseItemEffect(Packet& packet);
        static void handleNpcTalk(Packet& packet);
        static void handleNpcTalkMore(Packet& packet);
        static void handleNpcShop(Packet& packet);
        static void handleStorage(Packet& packet);
        static void handleHiredMerchantRequest(Packet& packet);
        static void handleDueyAction(Packet& packet);
        static void handleItemSort(Packet& packet);
        static void handleItemSort2(Packet& packet);
        static void handleItemMove(Packet& packet);
        static void handleUseItem(Packet& packet);
        static void handleCancelItemEffect(Packet& packet);
        static void handleUseSummonBag(Packet& packet);
        static void handleUseMountFood(Packet& packet);
        static void handleUseCashItem(Packet& packet);
        static void handleUseCatchItem(Packet& packet);
        static void handleUseSkillBook(Packet& packet);
        static void handleUseReturnScroll(Packet& packet);
        static void handleUseUpgradeScroll(Packet& packet);
        static void handleDistributeAP(Packet& packet);
        static void handleHealOverTime(Packet& packet);
        static void handleDistributeSP(Packet& packet);
        static void handleSpecialMove(Packet& packet);
        static void handleCancelBuff(Packet& packet);
        static void handleSkillEffect(Packet& packet);
        static void handleMesoDrop(Packet& packet);
        static void handleGiveFame(Packet& packet);
        static void handleCharInfoRequest(Packet& packet);
        static void handleCancelDebuff(Packet& packet);
        static void handleChangeMapSpecial(Packet& packet);
        static void handleUseInnerPortal(Packet& packet);
        static void handleVipAddMap(Packet& packet);
        static void handleQuestAction(Packet& packet);
        static void handleSkillMacro(Packet& packet);
        static void handleReportPlayer(Packet& packet);
        static void handlePartyChat(Packet& packet);
        static void handleWhisper(Packet& packet);
        static void handleSpouseChat(Packet& packet);
        static void handleMessenger(Packet& packet);
        static void handlePlayerShop(Packet& packet);
        static void handlePlayerInteraction(Packet& packet);
        static void handlePartyOperation(Packet& packet);
        static void handleDenyPartyRequest(Packet& packet);
        static void handleGuildOperation(Packet& packet);
        static void handleDenyGuildRequest(Packet& packet);
        static void handleBuddyListModify(Packet& packet);
        static void handleNoteAction(Packet& packet);
        static void handleUseDoor(Packet& packet);
        static void handleChangeKeymap(Packet& packet);
        static void handleRingAction(Packet& packet);
        static void handleAllianceOperation(Packet& packet);
        static void handleBbsOperation(Packet& packet);
        static void handleEnterMTS(Packet& packet);
        static void handlePetTalk(Packet& packet);
        static void handleUseSolomanItem(Packet& packet);
        static void handlePetAutoPot(Packet& packet);
        static void handleMoveSummon(Packet& packet);
        static void handleSummonAttack(Packet& packet);
        static void handleDamageSummon(Packet& packet);
        static void handleMoveLife(Packet& packet);
        static void handleAutoAggro(Packet& packet);
        static void handleMobDamageMob(Packet& packet);
        static void handleMonsterBomb(Packet& packet);
        static void handleNpcAction(Packet& packet);
        static void handleItemPickup(Packet& packet);
        static void handleDamageReactor(Packet& packet);
        static void handleMonsterCarnival(Packet& packet);
        static void handlePartySearchRegister(Packet& packet);
        static void handlePartySearchStart(Packet& packet);
        static void handlePlayerUpdate(Packet& packet);
        static void handleMapleTV(Packet& packet);
        static void handleMTSOperation(Packet& packet);
        static void handleTouchingCS(Packet& packet);
        static void handleBuyCSItem(Packet& packet);
        static void handleCouponCode(Packet& packet);
        static void handlePetSpawn(Packet& packet);
        static void handlePetMove(Packet& packet);
        static void handlePetChat(Packet& packet);
        static void handlePetCommand(Packet& packet);
        static void handlePetLoot(Packet& packet);
        static void handlePetFood(Packet& packet);

    public:
        static PacketHandlers m_packetHandlers;

    };
}