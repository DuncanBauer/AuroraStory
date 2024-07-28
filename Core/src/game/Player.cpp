#include "Player.h"

#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

Player::Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets) 
    : TCPConnection(std::move(socket), incomingPackets)
{}
    
Player::~Player()
{}

void Player::processPacket(Packet& packet)
{
    u16 opCode = util::PacketTool::readShort(packet);
    if (!PacketHandler::m_packetHandlers[opCode])
    {
        SERVER_ERROR("No handler for this opCode");
        return;
    }

    PacketHandler::m_packetHandlers[opCode](shared_from_this(), packet);
    //PacketHandler::m_packetHandlers[opCode](*this, packet);
}

void Player::loadAccountData()
{

}

u32 Player::login(const std::string& username, const std::string& password)
{
    if (m_attemptedLogins >= 5)
    {
        disconnect();
    }

    //if (loginsuccessful)
    //    m_attemptedLogins = 0;
    //else
    //    m_attemptedLogins++;

    return 0;
}

u32 Player::logout()
{
    return 0;
}

u32 Player::changeChannel()
{
    return 0;
}

void Player::banAccount()
{

}

bool Player::isGM()
{
    return m_isGM;
}

bool Player::isLoggedIn()
{
    return m_isLoggedIn;
}

bool Player::isGuestAccount()
{
    return m_isGuestAccount;
}

bool Player::isAccountBanned()
{
    return m_isBanned;
}

bool Player::hasBannedIp()
{
    std::vector<std::string> ips = Master::getIpBans();
    return std::find(ips.begin(), ips.end(), getIp()) != ips.end();
}

bool Player::hasBannedMac()
{
    std::vector<std::string> macs = Master::getMacBans();
    return std::find(macs.begin(), macs.end(), getIp()) != macs.end();
}