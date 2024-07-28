###TODO (In order?):

Login Queue
Packets
Wz File Reading ( Want to do yaml files but may go with just wz files for now (fuck xml))
Parties
Guilds
Quests
Alliances
Marriage
Rings
Combat

###Build Tools:
    [Premake](https://premake.github.io)
    [CMake](https://cmake.org)
    [Python](https://www.python.org)

###Dependencies:
    Git Submodules:
        [AES](https://github.com/BrianGladman/aes)
        [ASIO](https://github.com/chriskohlhoff/asio.git)
        [Bcrypt](https://github.com/trusch/libbcrypt.git)
        [rpclib](https://github.com/rpclib/rpclib.git)
        [Spdlog](https://github.com/gabime/spdlog.git)
        [Yaml-Cpp](https://github.com/jbeder/yaml-cpp.git)

    Vcpkgs:
        mongo-c-driver
        mongo-cxx-drive

#####Build instructions:
'python generate.py Debug|Release'

####Design Decisions:
#####Language - C++
    Speed
    I don't like java

#####Scripting - Lua
    Lighweight
    Easy to learn/use for beginners (Unlike javascript)

#####Databasing - MongoDB
    I'm more familiar with it than SQL at this point

#####Wz Parsing - YAML
    Xml is so 2008

#####System Architecture:

                                Login Server

                                /           \

                              /               \

                            /                   \

                          /                       \

                        /                           \

                     World1                       World2

                   /    |   \                    /   |   \

                  /     |    \                  /    |    \

                 /      |     \                /     |     \

                /       |      \              /      |      \

               /        |       \            /       |       \

           Channel1 Channel2 Channel3    Channel1 Channel2 Channel3

The Login Server is connected over RPC to each World Server, which in turn are
connected over RPC to their respective channel servers. Which allows for distribution of servers over multiple computers.