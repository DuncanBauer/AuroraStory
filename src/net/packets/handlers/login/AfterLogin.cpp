#include "net/packets/PacketCreator.h"
#include "net/packets/PacketHandler.h"
#include "util/PacketTool.h"

void PacketHandler::handleAfterLogin(std::shared_ptr<Player> player, Packet& packet)
{
    SERVER_INFO("handleAfterLogin");

    byte c2 = util::PacketTool::readByte(packet);
    byte c3 = util::PacketTool::readByte(packet);
    //byte c3 = 5;

    if (c2 == 1 && c3 == 1) 
    {
        // Official requests the pin here - but pins suck so we just accept
        player->send(PacketCreator::pinAccepted());
    }
    else if (c2 == 1 && c3 == 0) 
    {
        std::string pin = util::PacketTool::readMapleString(packet);
        if (pin == "1234") 
        {
            player->send(PacketCreator::pinAccepted());
        }
        else 
        {
            player->send(PacketCreator::requestPinAfterFailure());
        }
    }
    else {
        // abort login attempt
    }


    //if (packet.size() > 0)
    //{
    //    c3 = util::PacketTool::readByte(packet);
    //}

    //if (c2 == 1 && c3 == 1) 
    //{
    //    if (player->checkPin(""))
    //    {
    //        player->send(PacketCreator::registerPin());
    //    }
    //    else
    //    {
    //        player->send(PacketCreator::requestPin());
    //    }
    //}
    //else if (c2 == 1 && c3 == 0)
    //{
    //    std::string pin = util::PacketTool::readMapleString(packet);
    //    if (player->checkPin(pin))
    //    {
    //        player->send(PacketCreator::pinAccepted());
    //    }
    //    else
    //    {
    //        player->send(PacketCreator::requestPinAfterFailure());
    //    }
    //}
    //else if (c2 == 2 && c3 == 0)
    //{
    //    std::string pin = util::PacketTool::readMapleString(packet);
    //    if (player->checkPin(pin))
    //    {
    //        player->send(PacketCreator::registerPin());
    //    }
    //    else
    //    {
    //        player->send(PacketCreator::requestPinAfterFailure());
    //    }
    //}
    //else if (c2 == 0 && c3 == 5)
    //{
    //    player->disconnect();
    //    //c.updateLoginState(MapleClient.LOGIN_NOTLOGGEDIN);
    //}
}