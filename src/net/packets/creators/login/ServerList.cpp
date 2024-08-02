#include <set>

#include "Master.h"
#include "net/packets/PacketCreator.h"
#include "Typedefs.h"

namespace PacketCreator
{
    /**
     * Gets a packet detailing a server and its channels.
     *
     * @param serverIndex The index of the server to create information about.
     * @param serverName The name of the server.
     * @param channelLoad Load of the channel - 1200 seems to be max.
     * @return The server info packet.
     */
    Packet getServerData(u32 serverIndex, std::string serverName, std::map<u32, u32> channelLoad)
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_SERVER_LIST);
        util::PacketTool::writeIntAsByte(packet, serverIndex);
        util::PacketTool::writeMapleString(packet, serverName);
        util::PacketTool::writeIntAsByte(packet, Master::getInstance().getWorlds()[serverIndex]->getSettings().serverFlag);
        util::PacketTool::writeMapleString(packet, Master::getInstance().getWorlds()[serverIndex]->getSettings().eventMessage);

        util::PacketTool::writeIntAsByte(packet, 0x64); // rate modifier, don't ask O.O!
        util::PacketTool::writeIntAsByte(packet, 0x0); // event xp * 2.6 O.O!
        util::PacketTool::writeIntAsByte(packet, 0x64); // rate modifier, don't ask O.O!
        util::PacketTool::writeIntAsByte(packet, 0x0); // drop rate * 2.6
        util::PacketTool::writeIntAsByte(packet, 0x0);
        
        //int lastChannel = 1;
        //for (int i = 30; i > 0; i--)
        //{
        //    if(channelLoad[i])
        //    {
        //        lastChannel = i;
        //        std::cout << "lastChannel: " << lastChannel << '\n';
        //        break;
        //    }
        //}
        u32 channelCount = Master::getInstance().getWorlds()[serverIndex]->getChannelCount();
        //util::PacketTool::writeIntAsByte(packet, lastChannel);
        util::PacketTool::writeIntAsByte(packet, channelCount);

        int load;
        //for (int i = 1; i <= lastChannel; i++)
        for (int i = 1; i <= channelCount; i++)
        {
            if (channelLoad[i])
            {
                load = channelLoad[i];
            }
            else 
            {
                load = 1200;
            }

            util::PacketTool::writeMapleString(packet, serverName + "-" + std::to_string(i));
            util::PacketTool::writeInt(packet, load - 1200);
            util::PacketTool::writeIntAsByte(packet, 1);
            util::PacketTool::writeShort(packet, i - 1);
        }
        util::PacketTool::writeShort(packet, 0); // ver 0.56

        return packet;
    }

    /**
     * Gets a packet saying that the server list is over.
     *
     * @return The end of server list packet.
     */
    Packet getEndOfServerList()
    {
        Packet packet;
        util::PacketTool::writeShort(packet, SendOps::k_SERVER_LIST);
        util::PacketTool::writeIntAsByte(packet, 0xFF);
        return packet;
    }
}