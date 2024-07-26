#pragma once

#include <string>

namespace constant
{
    typedef unsigned char byte;

    constexpr std::size_t k_packetHandshakeServerLength = 13; // the size of the handshake packet
    constexpr short k_gameVersion = 62; // major game version
    constexpr short k_gameMinorVersion = 1; // minor game version, if 0, then the string is empty
    constexpr byte k_gmsLocale = 8;

    constexpr std::size_t k_ivBufferSize = 16;
    constexpr std::size_t k_headerSize = 4;
    const std::string k_gameFilePath = "C:/Nexon/Maplestory/";
}