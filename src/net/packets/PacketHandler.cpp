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
        m_packetHandlers[constant::RecvOps::k_LOGIN_PASSWORD]       = [this](net::Packet& packet) { handleLoginPassword(packet); };
        m_packetHandlers[constant::RecvOps::k_GUEST_LOGIN]          = [this](net::Packet& packet) { handleGuestLogin(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVERLIST_REREQUEST] = [this](net::Packet& packet) { handleServerListRerequest(packet); };
        m_packetHandlers[constant::RecvOps::k_CHARLIST_REQUEST]     = [this](net::Packet& packet) { handleCharListRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVERSTATUS_REQUEST] = [this](net::Packet& packet) { handleServerStatusRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_SET_GENDER]           = [this](net::Packet& packet) { handleSetGender(packet); };
        m_packetHandlers[constant::RecvOps::k_AFTER_LOGIN]          = [this](net::Packet& packet) { handleAfterLogin(packet); };
        m_packetHandlers[constant::RecvOps::k_REGISTER_PIN]         = [this](net::Packet& packet) { handleRegisterPin(packet); };
        m_packetHandlers[constant::RecvOps::k_SERVERLIST_REQUEST]   = [this](net::Packet& packet) { handleServerListRequest(packet); };
        m_packetHandlers[constant::RecvOps::k_PLAYER_DC]            = [this](net::Packet& packet) { handlePlayerDC(packet); };
        m_packetHandlers[constant::RecvOps::k_VIEW_ALL_CHAR]        = [this](net::Packet& packet) { handleViewAllChar(packet); };
        m_packetHandlers[constant::RecvOps::k_PICK_ALL_CHAR]        = [this](net::Packet& packet) { handlePickAllChar(packet); };
        m_packetHandlers[constant::RecvOps::k_CHAR_SELECT]          = [this](net::Packet& packet) { handleCharSelect(packet); };
        m_packetHandlers[constant::RecvOps::k_CHECK_CHAR_NAME]      = [this](net::Packet& packet) { handleCheckCharName(packet); };
        m_packetHandlers[constant::RecvOps::k_CREATE_CHAR]          = [this](net::Packet& packet) { handleCreateChar(packet); };
        m_packetHandlers[constant::RecvOps::k_DELETE_CHAR]          = [this](net::Packet& packet) { handleDeleteChar(packet); };
        m_packetHandlers[constant::RecvOps::k_CLIENT_START]         = [this](net::Packet& packet) { handleClientStart(packet); };
        m_packetHandlers[constant::RecvOps::k_RELOG]                = [this](net::Packet& packet) { handleRelog(packet); };
    }
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