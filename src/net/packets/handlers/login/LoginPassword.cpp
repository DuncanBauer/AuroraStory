#include "util/LoggingTool.h"
#include "util/PacketTool.h"
#include "util/MongoDb.h"
#include "util/HashPassword.h"

#include "Master.h"
#include "game/Player.h"
#include "net/packets/PacketHandler.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

void PacketHandler::handleLoginPassword(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("PacketHandler::handleLoginPassword");

    std::string username = util::PacketTool::readMapleString(packet);
    std::string password = util::PacketTool::readMapleString(packet);

    u16 loginSuccess = 5; // Account doesn't exist
    FindOneResult dbResult = util::MongoDb::getInstance().accountExists(username);

    // Username doesn't exist
    if (!dbResult)
    {
        if (Master::getInstance().getSettings().autoRegisterEnabled)
        {
            // Register new account and log in
            player->autoRegister(username, password);
            dbResult = util::MongoDb::getInstance().accountExists(username);
        }
        else
        {
            player->send(PacketCreator::getLoginFailed(loginSuccess));
            return;
        }
    }

    // Attempt login
    loginSuccess = player->login(username, password, *dbResult);

    // Correct password
    if (loginSuccess == 2)
    {
        player->send(PacketCreator::getLoginSuccess(username));
    }
    else
    {
        player->send(PacketCreator::getLoginFailed(loginSuccess));
    }
}
