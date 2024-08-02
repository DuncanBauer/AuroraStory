#include "Player.h"

#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/HashPassword.h"
#include "util/LoggingTool.h"
#include "util/MongoDb.h"
#include "util/PacketTool.h"

Player::Player(tcp::socket socket, util::ThreadSafeQueue<Packet>& incomingPackets) 
    : TCPConnection(std::move(socket), incomingPackets)
{}
    
Player::~Player()
{}

void Player::processPacket(Packet& packet)
{
    SERVER_INFO("Player recieved: {}", util::PacketTool::outputPacketHex(packet).str());
    u16 opCode = util::PacketTool::readShort(packet);
    if (!PacketHandler::m_packetHandlers[opCode])
    {
        SERVER_ERROR("No handler for this opCode");
        return;
    }

    PacketHandler::m_packetHandlers[opCode](std::static_pointer_cast<Player>(shared_from_this()), packet);
    //PacketHandler::m_packetHandlers[opCode](*this, packet);
}

void Player::loadAccountData(const bsoncxx::v_noabi::document::value& data)
{
    bsoncxx::document::view view = data.view();

    try
    {
        // Extract data from the BSON document
        m_account.accountId = view["_id"].get_oid().value.to_string();
        m_account.username = std::string(view["username"].get_string().value);

        if (view.find("pin") != view.end())
        {
            m_account.pin = std::string(view["pin"].get_string().value);
        }

        m_account.isGM = view["gm_level"].get_int32().value;
        m_account.isLoggedIn = view["logged_in"].get_int32().value;
        m_account.birthday = view["birthday"].get_int64().value;
        m_account.isBanned = view["banned"].get_bool().value;
        m_account.isGuestAccount = view["guest"].get_bool().value;
    
        if (view.find("ban_reason") != view.end())
        {
            m_account.banReason = view["ban_reason"].get_int32().value;
        }

        if (view.find("temp_ban") != view.end())
        {
            m_account.tempban = view["temp_ban"].get_int64().value;
        }
    }
    catch (std::exception e)
    {
        SERVER_ERROR("Player::loadAccountData exception: {}", e.what());
    }
}

void Player::autoRegister(const std::string& username, const std::string& password)
{
    std::string passwordHash = util::generateHash(password);
    util::MongoDb::getInstance().autoRegisterAccount(username, passwordHash, getIp());
}

void Player::banAccount()
{

}

u16 Player::login(const std::string& username, const std::string& password, const bsoncxx::v_noabi::document::value& data)
{
    //if (m_attemptedLogins >= 5)
    //{
    //    disconnect();
    //}

    loadAccountData(data);
    bsoncxx::document::view view = data.view();
    std::string passwordHash = std::string(view["password_hash"].get_string().value);
    bool passwordVerified = util::verifyPassword(password, passwordHash);

    if (m_account.isBanned)
    {
        return 2;
    }

    if (m_account.isLoggedIn)
    {
        return 7;
    }

    if (!passwordVerified)
    {
        return 4;
    }

    return 2;

    //if (loginsuccessful)
    //    m_attemptedLogins = 0;
    //else
    //    m_attemptedLogins++;
}

u32 Player::logout()
{
    return 0;
}

std::string Player::getPin()
{
    return m_account.pin;
}

void Player::setPin(std::string pin)
{
    m_account.pin = pin;
    util::MongoDb::getInstance().setPin(m_account.username, pin);
}

bool Player::checkPin(std::string pin)
{
    return m_account.pin == pin;
}

u32 Player::changeChannel()
{
    return 0;
}

bool Player::isGM()
{
    return m_account.isGM;
}

bool Player::isLoggedIn()
{
    return m_account.isLoggedIn;
}

bool Player::isGuestAccount()
{
    return m_account.isGuestAccount;
}

bool Player::isAccountBanned()
{
    return m_account.isBanned;
}

bool Player::hasBannedIP()
{
    //std::vector<std::string> ips = Master::getBannedIPs();
    //return std::find(ips.begin(), ips.end(), getIp()) != ips.end();
    return false;
}

bool Player::hasBannedMAC()
{
    //std::vector<std::string> macs = Master::getBannedMACs();
    //return std::find(macs.begin(), macs.end(), getIp()) != macs.end();
    return false;
}