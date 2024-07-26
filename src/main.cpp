#include "pch.h"

#include "Master.h"
#include "util/Logger.h"
#include "net/packets/PacketCreator.h"
#include "util/HashPassword.h"

int main(int argc, char** argv)
{
    Master master;
    master.run();

    //std::string password = "duncan";
    //std::string hashedPassword = util::generateHash(password);
    //std::cout << "PASSWORD: " << password << '\n';
    //std::cout << "HASHED PASSWORD: " << hashedPassword << '\n';

    //if (util::verifyPassword(password, hashedPassword))
    //    std::cout << "PASSWORD CORRECT\n";
    //else
    //    std::cout << "PASSWORD INCORRECT\n";

    std::cin.get();
}