#include <iostream>

#include "Master.h"

int main(int argc, char** argv)
{
    try
    {
        Master master;
        master.run();
    }
    catch (std::exception e)
    {
        SERVER_ERROR("{}", e.what());
    }
    std::cin.get();
}