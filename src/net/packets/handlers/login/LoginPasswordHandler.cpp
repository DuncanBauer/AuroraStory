#include "util/LoggingTool.h"
#include "util/PacketTool.h"
#include "util/MongoDb.h"
#include "util/HashPassword.h"

#include "Master.h"
#include "game/Player.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"

enum LoginStatus
{
    LOGIN_SUCCESS,
    LOGIN_FAIL,
    BANNED
};

void PacketHandler::handleLoginPassword(Player& player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleLoginPassword");

    std::string username = util::PacketTool::readMapleString(packet);
    std::string password = util::PacketTool::readMapleString(packet);

    SERVER_INFO("Username: {}", username);
    SERVER_INFO("Password: {}", password);

    //player.login(username, password);

    //if (!util::MongoDb::accountExists(username))
    //{
    //    if (Master::getServerSettings().autoRegisterEnabled)
    //    {
    //        std::string passwordHash = util::generateHash(password);
    //        if (util::MongoDb::autoRegisterAccount(username, passwordHash, player.getIP()))
    //        {

    //        }
    //    }
    //}

    if (player.isBanned()
    {
        player.send(PacketCreator::getPermaBan());
        return;
    }

    if (!accountExists)
    {
        if (autoRegisterEnabled)
        {
            bool registerSuccess = player.send(PacketCreator::getAutoRegister());
            if (!registerSuccess)
            {
                player.send(PacketCreator::getLoginFailed());
                return;
            }
        }
        else
        {
            player.send(PacketCreator::getLoginFailed());
            return
        }
    }

    addToLoginQueue(player, player.isGM());
}
