#pragma once

#include <iomanip>
#include <sstream>
#include <vector>

namespace util
{
    typedef unsigned char byte;

    std::stringstream outputPacketHex(std::vector<byte> packet)
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
        ss << std::dec << '\n';

        return ss;
    }

    std::stringstream outputPacketString(std::vector<byte> packet)
    {
        std::stringstream ss;
        for (byte val : packet)
        {
            ss << val << ' ';
        }
        ss << std::dec << '\n';

        return ss;
    }
}