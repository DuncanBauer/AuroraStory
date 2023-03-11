// Aurora Maple Library, v0.0.1 ALPHA
// Header file

// For more information visit: https://github.com/DuncanBauer/ProjectAurora#table-of-contents

// Developed by Duncan Bauer and every direct or indirect contributors to the GitHub.
// LICENSING INFORMATION

// It is recommended that you don't modify any source code! It will become difficult for you to update the library.
// Note that 'Aurora::' being a namespace, you can add functions into the namespace from your own source files, without
// modifying Util.h or Util.cpp. Discussing your changes on the GitHub Issue Tracker may lead you
// to a better solution or official support for them.

// Index of this file:
// CODE
//   - [SECTION] PREPROCESSOR DIRECTIVES
//   - [SECTION] INCLUDES
//   - [SECTION] FORWARD DECLARATIONS
//   - [SECTION] TYPENAMES
//   - [SECTION] CONSTANTS
//   - [SECTION] CLASSES
//   - [SECTION] STRUCTS
//   - [SECTION] FUNCTIONS
//   - [SECTION] MACROS

/************************************************************************************
* [SECTION] PREPROCESSOR DIRECTIVES
************************************************************************************/
#pragma once


// Define dllexport and dllimport for Windows
#ifdef PA_PLATFORM_WINDOWS
  #ifdef PA_MAPLE_BUILD_DLL
    #define AURORA_MAPLE_API _declspec(dllexport)
  #else
    #define AURORA_MAPLE_API _declspec(dllimport)
  #endif
#else
  #error PROJECT AURORA ONLY SUPPORTS WINDOWS!
#endif
#pragma endregion

// Library Version
// (Integer encoded as XYYZZ for use in #if preprocessor conditionals, e.g. '#if AURORA_UTIL_VERSION_NUM > 12345')
#define AURORA_MAPLE_VERSION     "0.0.1 ALPHA"
#define AURORA_MAPLE_VERSION_NUM 00001

/************************************************************************************
* [SECTION] INCLUDES
************************************************************************************/
// Project Specific Headers

// C++ Standard Library Headers

// Third Party Library Headers

/************************************************************************************
* [SECTION] FORWARD DECLARATIONS
************************************************************************************/

/************************************************************************************
* [SECTION] TYPENAMES
************************************************************************************/

/************************************************************************************
* [SECTION] CONSTANTS
************************************************************************************/

/************************************************************************************
* [SECTION] CLASSES
************************************************************************************/

/************************************************************************************
* [SECTION] STRUCTS
************************************************************************************/

/************************************************************************************
* [SECTION] FUNCTIONS
************************************************************************************/

/************************************************************************************
* [SECTION] MACROS
************************************************************************************/