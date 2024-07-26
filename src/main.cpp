#include <iostream>

#include "Master.h"
#include "util/Logger.h"
#include "net/packets/PacketCreator.h"
#include "util/HashPassword.h"

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

    // Initialize Logger
    util::Logger::init();

    Master master;

    // Read config
    std::cout << master.getConfig()["gameVersion"].as<std::string>() << '\n';

    //std::string password = "duncan";
    //std::string hashedPassword = util::generateHash(password);
    //std::cout << "PASSWORD: " << password << '\n';
    //std::cout << "HASHED PASSWORD: " << hashedPassword << '\n';

    //if (util::verifyPassword(password, hashedPassword))
    //    std::cout << "PASSWORD CORRECT\n";
    //else
    //    std::cout << "PASSWORD INCORRECT\n";

    master.run();

    std::cin.get();
}