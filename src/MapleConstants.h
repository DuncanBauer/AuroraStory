#pragma once

#include <string>

constexpr std::size_t k_packetHandshakeServerLength = 13; // the size of the handshake packet
constexpr short k_gameVersion = 62; // mayor game version
const std::string k_gameMinorVersion = "1"; // minor game version, if 0, then the string is empty

namespace GameLocales
{
	const signed char kGlobalMapleStory = 8;
}

constexpr unsigned char kGameLocale = GameLocales::kGlobalMapleStory;

// standard install path would be: "C:\\Nexon\\MapleStory\\"
const std::string kGameFilePath = "C:/Nexon/Maplestory/";