Dependencies:
    build tools:
    CMake
    Python

    as git submodules:
    AES
    ASIO
    Bcrypt
    Spdlog
    Yaml-Cpp

    as vcpkgs:
    BsonC
    BsonCXX
    MongoC
    MongoCXX

Build instructions:
'python generate.py Debug|Release'

Design Decisions:
C++ for source language:
    Speed
    I don't like java

Lua for scripting:
    Lighweight
    Easy to learn/use for beginners (Unlike javascript)

MongoDB for databasing:
    I'm more familiar with it than SQL at this point

Yaml for Wz:
    Xml is so 2008

TODO (In order?):
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