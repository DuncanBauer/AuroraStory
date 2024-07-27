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

    player.login(username, password);
    u16 loginOk = 0;

    // If username doesn't exist
    if (!util::MongoDb::accountExists(username))
    {
        if (Master::getServerSettings().autoRegisterEnabled)
        {
            std::string passwordHash = util::generateHash(password);
            if (util::MongoDb::autoRegisterAccount(username, passwordHash, player.getIP()))
            {

            }
        }
    }
        // check ban status
        // check password hash
    // else
        // if auto register enabled
            // register
}
