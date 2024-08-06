#include <iostream>
#include <memory>
#include <vector>

#include "Master.h"
#include "provider/wz/nx/NxFile.h"

int main(int argc, char** argv)
{
    try
    {
        std::filesystem::path path("wz/nx/Sound.nx");
        Provider::NxFile file(path);


        //Master& master = Master::getInstance();
        //master.run();
    }
    catch (std::exception e)
    {
        SERVER_ERROR("{}", e.what());
    }

    std::cin.get();
}
