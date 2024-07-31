
# AuroraStory

### TODO:
    Pretty much everything

## Requirements:

### Build Tools:
Currently the project requires all of these tools as the git submodules are currently built with CMake even though the AuroraStory project itself uses Premake to generate project files. This is done via Python scripts to build both the dependencies and the project itself with a single console command. In the future I'll write premake5.lua files for these dependencies as well. 

* Docker
* [CMake](https://cmake.org)
* C++ Compiler
* [Python](https://www.python.org)
* [Premake](https://premake.github.io)

### Dependencies:
* [AES](https://github.com/BrianGladman/aes)
* [ASIO](https://github.com/chriskohlhoff/asio.git)
* [Bcrypt](https://github.com/trusch/libbcrypt.git)
* [Mongo-c-driver](https://github.com/mongodb/mongo-c-driver)
* [Mongo-cxx-driver](https://github.com/mongodb/mongo-cxx-driver)
* [Spdlog](https://github.com/gabime/spdlog.git)
* [Yaml-Cpp](https://github.com/jbeder/yaml-cpp.git)

For the life of me I couldn't get the MongoDB drivers to build from source files on my current PC, so I resigned myself to using Vcpkg to download them even though it's not cross-platform. This will have to change in the future. Note: The Mongo-cxx-driver depends on the Mongo-c-driver, as such both are required.

## Build Instructions:

## Run Instructions:

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