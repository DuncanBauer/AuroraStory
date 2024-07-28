#pragma once

#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define AURORA_SERVER_API __declspec(dllexport)
    #else
        #define AURORA_SERVER_API __declspec(dllimport)
    #endif
#else
    #define AURORA_SERVER_API
#endif