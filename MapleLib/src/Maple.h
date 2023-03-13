#pragma once

// Define dllexport and dllimport for Windows
#ifdef PA_PLATFORM_WINDOWS
    #ifdef PA_MAPLE_BUILD_DLL
        #define AURORA_MAPLE_API _declspec(dllexport)
    #else
        #define AURORA_MAPLE_API _declspec(dllimport)
    #endif
#else
    #define AURORA_MAPLE_API 
//  #error PROJECT AURORA ONLY SUPPORTS WINDOWS!
#endif
#pragma endregion

#define AURORA_MAPLE_LIB_VERSION     "0.0.1 ALPHA"
#define AURORA_MAPLE_LIB_VERSION_NUM 00001

// Includes
#include <vector>

// Typedefs
using byte = unsigned char;
using ByteBuffer = std::vector<byte>;

// Declarations
short MapleVersion;