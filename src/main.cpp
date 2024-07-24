#include <iostream>

#include "util/Logger.h"
#include "net/world/World.h"

int main(int argc, char** argv)
{
    util::Logger::init();

    net::World world;
    world.run();
}