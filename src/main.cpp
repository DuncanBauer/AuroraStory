#include <iostream>

#include "util/Logger.h"
#include "net/world/World.h"
#include "net/packets/PacketCreator.h"

int main(int argc, char** argv)
{
    //typedef unsigned char byte;
    //std::vector<byte> recv(16);
    //std::vector<byte> send(16);
    //
    //net::PacketCreator creator;
    //creator.getHandshake(recv, send);
    //std::vector<byte> packet = creator.getPacketBuffer();
    //
    //std::cout << '\n' << std::dec << packet.size() << '\n';
    //for (byte val : packet)
    //    std::cout << std::hex
    //    << std::uppercase    // Print letters in uppercase (A-F)
    //    << std::setfill('0') // Fill with zeroes if necessary
    //    << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
    //    << "0x" << (int)(val & 0xFF) << ' ';
    //std::cout << '\n';

    util::Logger::init();

    net::World world;
    world.run();

    std::cin.get();
}