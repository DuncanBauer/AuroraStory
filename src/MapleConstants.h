#pragma once

#include <string>

constexpr std::size_t k_packetHandshakeServerLength = 13; // the size of the handshake packet
constexpr short k_gameVersion = 62; // major game version
const std::string k_gameMinorVersion = ""; // minor game version, if 0, then the string is empty
constexpr std::size_t k_ivBufferSize = 16;
constexpr std::size_t k_headerSize = 4;
constexpr unsigned char k_gmsLocale = 8;

const std::string k_gameFilePath = "C:/Nexon/Maplestory/";