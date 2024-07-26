#include "PacketHandler.h"

#include "constants/PacketConstant.h"

namespace net
{
    void PacketHandler::registerHandlers()
    {
        m_packetHandlers[static_cast<byte>(constant::RecvOps::k_PONG)] = [this](net::Packet& packet) { handlePong(packet); };
    }
//        // GENERAL
//        void handlePong(Packet& packet) {}
//
//        // LOGIN
//        void handleGuestLogin(Packet& packet) {}
//        void handleServerListRerequest(Packet& packet) {}
//        void handleCharListRequest(Packet& packet) {}
//        void handleServerStatusRequest(Packet& packet) {}
//        void handleSetGender(Packet& packet) {}
//        void handleAfterLogin(Packet& packet) {}
//        void handleRegisterPin(Packet& packet) {}
//        void handleServerListRequest(Packet& packet) {}
//        void handlePlayerDC(Packet& packet) {}
//        void handleViewAllChar(Packet& packet) {}
//        void handlePickAllChar(Packet& packet) {}
//        void handleCharSelect(Packet& packet) {}
//        //void handleCheckCharName(Packet& packet) {}
//        //void handleCreateChar(Packet& packet) {}
//        //void handleDeleteChar(Packet& packet) {}
//        void handleClientStart(Packet& packet) {}
//        void handleRelog(Packet& packet) {}
//
//        // CHANNEL
//        void handlePlayerLoggedIn(Packet& packet) {}
//        void handleStrangeData(Packet& packet) {}
//        void handleChangeMap(Packet& packet) {}
//        void handleChangeChannel(Packet& packet) {}
//        void handleEnterCashShop(Packet& packet) {}
//        void handleMovePlayer(Packet& packet) {}
//        void handleCancelChair(Packet& packet) {}
//        void handleUseChair(Packet& packet) {}
//        void handleCloseRangeAttack(Packet& packet) {}
//        void handleRangedAttack(Packet& packet) {}
//        void handleMagicAttack(Packet& packet) {}
//        void handleEnergyOrbAttack(Packet& packet) {}
//        void handleTakeDamage(Packet& packet) {}
//        void handleGeneralChat(Packet& packet) {}
//        void handleCloseChalkboard(Packet& packet) {}
//        void handleFaceExpression(Packet& packet) {}
//        void handleUseItemEffect(Packet& packet) {}
//        void handleNpcTalk(Packet& packet) {}
//        void handleNpcTalkMore(Packet& packet) {}
//        void handleNpcShop(Packet& packet) {}
//        void handleStorage(Packet& packet) {}
//        void handleHiredMerchantRequest(Packet& packet) {}
//        void handleDueyAction(Packet& packet) {}
//        void handleItemSort(Packet& packet) {}
//        void handleItemSort2(Packet& packet) {}
//        void handleItemMove(Packet& packet) {}
//        void handleUseItem(Packet& packet) {}
//        void handleCancelItemEffect(Packet& packet) {}
//        void handleUseSummonBag(Packet& packet) {}
//        void handleUseMountFood(Packet& packet) {}
//        void handleUseCashItem(Packet& packet) {}
//        void handleUseCatchItem(Packet& packet) {}
//        void handleUseSkillBook(Packet& packet) {}
//        void handleUseReturnScroll(Packet& packet) {}
//        void handleUseUpgradeScroll(Packet& packet) {}
//        void handleDistributeAP(Packet& packet) {}
//        void handleHealOverTime(Packet& packet) {}
//        void handleDistributeSP(Packet& packet) {}
//        void handleSpecialMove(Packet& packet) {}
//        void handleCancelBuff(Packet& packet) {}
//        void handleSkillEffect(Packet& packet) {}
//        void handleMesoDrop(Packet& packet) {}
//        void handleGiveFame(Packet& packet) {}
//        void handleCharInfoRequest(Packet& packet) {}
//        void handleCancelDebuff(Packet& packet) {}
//        void handleChangeMapSpecial(Packet& packet) {}
//        void handleUseInnerPortal(Packet& packet) {}
//        void handleVipAddMap(Packet& packet) {}
//        void handleQuestAction(Packet& packet) {}
//        void handleSkillMacro(Packet& packet) {}
//        void handleReportPlayer(Packet& packet) {}
//        void handlePartyChat(Packet& packet) {}
//        void handleWhisper(Packet& packet) {}
//        void handleSpouseChat(Packet& packet) {}
//        void handleMessenger(Packet& packet) {}
//        void handlePlayerO(Packet& packet) {}
//        void handlePlayerInteraction(Packet& packet) {}
//        void handlePartyOperation(Packet& packet) {}
//        void handleDenyPartyRequest(Packet& packet) {}
//        void handleGuildOperation(Packet& packet) {}
//        void handleDenyGuildRequest(Packet& packet) {}
//        void handleBuddyListModify(Packet& packet) {}
//        void handleNoteAction(Packet& packet) {}
//        void handleUserDoor(Packet& packet) {}
//        void handleChangeKeymap(Packet& packet) {}
//        void handleRingAction(Packet& packet) {}
//        void handleAllianceOperation(Packet& packet) {}
//        void handleBbsOperation(Packet& packet) {}
//        void handleEnterMTS(Packet& packet) {}
//        void handlePetTalk(Packet& packet) {}
//        void handleUseSolomanItem(Packet& packet) {}
//        void handlePetAutoPot(Packet& packet) {}
//        void handleMoveSummon(Packet& packet) {}
//        void handleSummonAttack(Packet& packet) {}
//        void handleDamageSummon(Packet& packet) {}
//        void handleMoveLife(Packet& packet) {}
//        void handleAutoAggro(Packet& packet) {}
//        void handleMobDamageMob(Packet& packet) {}
//        void handleMonsterBomb(Packet& packet) {}
//        void handleNpcAction(Packet& packet) {}
//        void handleItemPickup(Packet& packet) {}
//        void handleDamageReactor(Packet& packet) {}
//        void handleMonsterCarnival(Packet& packet) {}
//        void handlePartySearchRegister(Packet& packet) {}
//        void handlePartySearchStart(Packet& packet) {}
//        void handlePlayerUpdate(Packet& packet) {}
//        void handleMapleTV(Packet& packet) {}
//        void handleMTSOp(Packet& packet) {}
//
//        // CASHSHOP
//        void handleTouchingCS(Packet& packet) {}
//        void handleBuyCSItem(Packet& packet) {}
//        void handleCouponCode(Packet& packet) {}
//
//        // PET
//        void handleSpawnPet(Packet& packet) {}
//        void handleMovePet(Packet& packet) {}
//        void handlePetChat(Packet& packet) {}
//        void handlePetCommand(Packet& packet) {}
//        void handlePetLoot(Packet& packet) {}
//        void handlePetFood(Packet& packet) {}
}