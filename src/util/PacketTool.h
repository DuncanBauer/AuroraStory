#pragma once

#include <iomanip>
#include <sstream>
#include <vector>

namespace util
{
    typedef unsigned char byte;

    inline std::stringstream outputShortHex(short packetShort)
    {
        std::stringstream ss;
        ss << "0x"
            << std::uppercase    // Print letters in uppercase (A-F)
            << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
            << std::setfill('0') // Fill with zeroes if necessary
            << std::hex
            << (int)(packetShort & 0xFF)
            << ' ';
        ss << std::dec << '\n';

        return ss;
    }

    inline std::stringstream outputByteHex(byte packetByte)
    {
        std::stringstream ss;
        ss << "0x"
            << std::uppercase    // Print letters in uppercase (A-F)
            << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
            << std::setfill('0') // Fill with zeroes if necessary
            << std::hex
            << (int)(packetByte & 0xFF)
            << ' ';
        ss << std::dec;

        return ss;
    }

    inline std::stringstream outputPacketHex(Packet packet)
    {
        std::stringstream ss;
        for (byte val : packet)
        {
            ss << "0x"
                << std::uppercase    // Print letters in uppercase (A-F)
                << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
                << std::setfill('0') // Fill with zeroes if necessary
                << std::hex
                << (int)(val & 0xFF)
                << ' ';
        }
        ss << std::dec;

        return ss;
    }

    inline std::stringstream outputPacketDec(Packet packet)
    {
        std::stringstream ss;
        for (byte val : packet)
        {
            ss << (int)val << ' ';
        }
        ss << std::dec;

        return ss;
    }

    inline std::stringstream outputPacketString(Packet packet)
    {
        std::stringstream ss;
        for (byte val : packet)
        {
            ss << (char)val << ' ';
        }
        ss << std::dec;

        return ss;
    }
}