
# AuroraStory

### TODO:
    Pretty much everything

## Requirements:

### Build Tools:
Currently the project requires all of these tools as the git submodules are currently built with CMake even though the AuroraStory project itself uses Premake to generate project files. This is done via Python scripts to build both the dependencies and the project itself with a single console command. In the future I'll write premake5.lua files for these dependencies as well. 

* [Python](https://www.python.org)
* [Premake](https://premake.github.io)
* [CMake](https://cmake.org)
* C++ Compiler

### Dependencies:
* [AES](https://github.com/BrianGladman/aes)
* [ASIO](https://github.com/chriskohlhoff/asio.git)
* [Bcrypt](https://github.com/trusch/libbcrypt.git)
* [rpclib](https://github.com/rpclib/rpclib.git)
* [Spdlog](https://github.com/gabime/spdlog.git)
* [Yaml-Cpp](https://github.com/jbeder/yaml-cpp.git)
* [Mongo-c-driver](https://github.com/mongodb/mongo-c-driver)
* [Mongo-cxx-driver](https://github.com/mongodb/mongo-cxx-driver)

For the life of me I couldn't get the MongoDB drivers to build from source files on my current PC, so I resigned myself to using Vcpkg to download them even though it's not cross-platform. This will have to change in the future. Note: The Mongo-cxx-driver depends on the Mongo-c-driver, as such both are required.

## Build Instructions:
### It's important to note that these most of these steps aren't yet functional

To build project dependencies and generate the project files run:

    python generate.py Debug|Release

Once the project files are generated and the dependencies are built you can build AuroraStory by running:

    python buildAll.py Debug|Release

### Or if you wish to build the executables separately:

To build the LoginServer run:
    
    python buildLogin.py Debug|Release

To build the WorldServer run:
    
    python buildWorld.py Debug|Release

To build the ChannelServer run:
    
    python buildChannel.py Debug|Release


## Run Instructions:
### It's important to note that these most of these steps aren't yet functional
The order matters!

    LoginServer -> WorldServer(s) -> ChannelServer(s)

To run the project, first you must launch the LoginServer.

    python launchLogin.py Debug|Release

Then the WorldServer for as many Worlds as you plan to have. These Worlds can be hosted on separate computers as they communicate with the LoginServer and ChannelServers via RPC, However this will require you to modify the config.yaml file.

    python launchWorlds.py [worldCount] Debug|Release

Finally launch the ChannelServer for as many Channels as you plan to have, this will require you knowing the IP and Port of its respective WorldServer.

    python launchChannels.py [worldIP] [worldPort] [channelCount] Debug|Release

## Design Decisions:
##### Language - C++
* Speed
* I don't like Java

##### Scripting - Lua
* Lighweight
* Easy to learn/use for beginners
* I really don't like JavaScript

##### Databasing - MongoDB
* I'm more familiar with it than SQL at this point

##### Wz Parsing - YAML
* Xml is so 2008
* I'm already using Yaml-cpp to read configuration files anyways

##### System Architecture:

                        Login Server
                        /           \
                    /                   \
                /                           \
                World1                       World2
              /    |   \                    /   |   \
            /      |     \                /     |     \
          /        |       \            /       |       \
    Channel1 Channel2 Channel3    Channel1 Channel2 Channel3

The Login Server is connected via RPC to each World Server, which in turn are connected via RPC to their respective channel servers. Which allows for distribution of servers over multiple computers.