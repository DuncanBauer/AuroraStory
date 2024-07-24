#include "PacketHandler.h"

namespace net
{
    namespace PacketHandler
    {
        // GENERAL
        void handlePong(clientConnection client, Packet& packet) {}

        // LOGIN
        void handleLoginPassword(clientConnection client, Packet& packet) {}
        void handleGuestLogin(clientConnection client, Packet& packet) {}
        void handleServerListRerequest(clientConnection client, Packet& packet) {}
        void handleCharListRequest(clientConnection client, Packet& packet) {}
        void handleServerStatusRequest(clientConnection client, Packet& packet) {}
        void handleSetGender(clientConnection client, Packet& packet) {}
        void handleAfterLogin(clientConnection client, Packet& packet) {}
        void handleRegisterPin(clientConnection client, Packet& packet) {}
        void handleServerListRequest(clientConnection client, Packet& packet) {}
        void handlePlayerDC(clientConnection client, Packet& packet) {}
        void handleViewAllChar(clientConnection client, Packet& packet) {}
        void handlePickAllChar(clientConnection client, Packet& packet) {}
        void handleCharSelect(clientConnection client, Packet& packet) {}
        //void handleCheckCharName(clientConnection client, Packet& packet) {}
        //void handleCreateChar(clientConnection client, Packet& packet) {}
        //void handleDeleteChar(clientConnection client, Packet& packet) {}
        void handleClientStart(clientConnection client, Packet& packet) {}
        void handleRelog(clientConnection client, Packet& packet) {}

        // CHANNEL
        void handlePlayerLoggedIn(clientConnection client, Packet& packet) {}
        void handleStrangeData(clientConnection client, Packet& packet) {}
        void handleChangeMap(clientConnection client, Packet& packet) {}
        void handleChangeChannel(clientConnection client, Packet& packet) {}
        void handleEnterCashShop(clientConnection client, Packet& packet) {}
        void handleMovePlayer(clientConnection client, Packet& packet) {}
        void handleCancelChair(clientConnection client, Packet& packet) {}
        void handleUseChair(clientConnection client, Packet& packet) {}
        void handleCloseRangeAttack(clientConnection client, Packet& packet) {}
        void handleRangedAttack(clientConnection client, Packet& packet) {}
        void handleMagicAttack(clientConnection client, Packet& packet) {}
        void handleEnergyOrbAttack(clientConnection client, Packet& packet) {}
        void handleTakeDamage(clientConnection client, Packet& packet) {}
        void handleGeneralChat(clientConnection client, Packet& packet) {}
        void handleCloseChalkboard(clientConnection client, Packet& packet) {}
        void handleFaceExpression(clientConnection client, Packet& packet) {}
        void handleUseItemEffect(clientConnection client, Packet& packet) {}
        void handleNpcTalk(clientConnection client, Packet& packet) {}
        void handleNpcTalkMore(clientConnection client, Packet& packet) {}
        void handleNpcShop(clientConnection client, Packet& packet) {}
        void handleStorage(clientConnection client, Packet& packet) {}
        void handleHiredMerchantRequest(clientConnection client, Packet& packet) {}
        void handleDueyAction(clientConnection client, Packet& packet) {}
        void handleItemSort(clientConnection client, Packet& packet) {}
        void handleItemSort2(clientConnection client, Packet& packet) {}
        void handleItemMove(clientConnection client, Packet& packet) {}
        void handleUseItem(clientConnection client, Packet& packet) {}
        void handleCancelItemEffect(clientConnection client, Packet& packet) {}
        void handleUseSummonBag(clientConnection client, Packet& packet) {}
        void handleUseMountFood(clientConnection client, Packet& packet) {}
        void handleUseCashItem(clientConnection client, Packet& packet) {}
        void handleUseCatchItem(clientConnection client, Packet& packet) {}
        void handleUseSkillBook(clientConnection client, Packet& packet) {}
        void handleUseReturnScroll(clientConnection client, Packet& packet) {}
        void handleUseUpgradeScroll(clientConnection client, Packet& packet) {}
        void handleDistributeAP(clientConnection client, Packet& packet) {}
        void handleHealOverTime(clientConnection client, Packet& packet) {}
        void handleDistributeSP(clientConnection client, Packet& packet) {}
        void handleSpecialMove(clientConnection client, Packet& packet) {}
        void handleCancelBuff(clientConnection client, Packet& packet) {}
        void handleSkillEffect(clientConnection client, Packet& packet) {}
        void handleMesoDrop(clientConnection client, Packet& packet) {}
        void handleGiveFame(clientConnection client, Packet& packet) {}
        void handleCharInfoRequest(clientConnection client, Packet& packet) {}
        void handleCancelDebuff(clientConnection client, Packet& packet) {}
        void handleChangeMapSpecial(clientConnection client, Packet& packet) {}
        void handleUseInnerPortal(clientConnection client, Packet& packet) {}
        void handleVipAddMap(clientConnection client, Packet& packet) {}
        void handleQuestAction(clientConnection client, Packet& packet) {}
        void handleSkillMacro(clientConnection client, Packet& packet) {}
        void handleReportPlayer(clientConnection client, Packet& packet) {}
        void handlePartyChat(clientConnection client, Packet& packet) {}
        void handleWhisper(clientConnection client, Packet& packet) {}
        void handleSpouseChat(clientConnection client, Packet& packet) {}
        void handleMessenger(clientConnection client, Packet& packet) {}
        void handlePlayerO(clientConnection client, Packet& packet) {}
        void handlePlayerInteraction(clientConnection client, Packet& packet) {}
        void handlePartyOperation(clientConnection client, Packet& packet) {}
        void handleDenyPartyRequest(clientConnection client, Packet& packet) {}
        void handleGuildOperation(clientConnection client, Packet& packet) {}
        void handleDenyGuildRequest(clientConnection client, Packet& packet) {}
        void handleBuddyListModify(clientConnection client, Packet& packet) {}
        void handleNoteAction(clientConnection client, Packet& packet) {}
        void handleUserDoor(clientConnection client, Packet& packet) {}
        void handleChangeKeymap(clientConnection client, Packet& packet) {}
        void handleRingAction(clientConnection client, Packet& packet) {}
        void handleAllianceOperation(clientConnection client, Packet& packet) {}
        void handleBbsOperation(clientConnection client, Packet& packet) {}
        void handleEnterMTS(clientConnection client, Packet& packet) {}
        void handlePetTalk(clientConnection client, Packet& packet) {}
        void handleUseSolomanItem(clientConnection client, Packet& packet) {}
        void handlePetAutoPot(clientConnection client, Packet& packet) {}
        void handleMoveSummon(clientConnection client, Packet& packet) {}
        void handleSummonAttack(clientConnection client, Packet& packet) {}
        void handleDamageSummon(clientConnection client, Packet& packet) {}
        void handleMoveLife(clientConnection client, Packet& packet) {}
        void handleAutoAggro(clientConnection client, Packet& packet) {}
        void handleMobDamageMob(clientConnection client, Packet& packet) {}
        void handleMonsterBomb(clientConnection client, Packet& packet) {}
        void handleNpcAction(clientConnection client, Packet& packet) {}
        void handleItemPickup(clientConnection client, Packet& packet) {}
        void handleDamageReactor(clientConnection client, Packet& packet) {}
        void handleMonsterCarnival(clientConnection client, Packet& packet) {}
        void handlePartySearchRegister(clientConnection client, Packet& packet) {}
        void handlePartySearchStart(clientConnection client, Packet& packet) {}
        void handlePlayerUpdate(clientConnection client, Packet& packet) {}
        void handleMapleTV(clientConnection client, Packet& packet) {}
        void handleMTSOp(clientConnection client, Packet& packet) {}

        // CASHSHOP
        void handleTouchingCS(clientConnection client, Packet& packet) {}
        void handleBuyCSItem(clientConnection client, Packet& packet) {}
        void handleCouponCode(clientConnection client, Packet& packet) {}

        // PET
        void handleSpawnPet(clientConnection client, Packet& packet) {}
        void handleMovePet(clientConnection client, Packet& packet) {}
        void handlePetChat(clientConnection client, Packet& packet) {}
        void handlePetCommand(clientConnection client, Packet& packet) {}
        void handlePetLoot(clientConnection client, Packet& packet) {}
        void handlePetFood(clientConnection client, Packet& packet) {}
    };
}