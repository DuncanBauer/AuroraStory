#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "Typedefs.h"

namespace util
{
    class PacketTool
    {
    public:
        PacketTool() = delete;

        static inline byte readByte(Packet& packet)
        {
            byte result = packet.front();
            packet.erase(packet.begin());
            return result;
        }

        static inline u16 readShort(Packet& packet)
        {
            u16 r1, r2;
            u16 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);

            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline i16 readSignedShort(Packet& packet)
        {
            i16 r1, r2;
            i16 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);

            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline u32 readInt(Packet& packet)
        {
            u32 r1, r2, r3, r4;
            u32 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);
            r3 = readByte(packet);
            r4 = readByte(packet);

            result |= r4 << 24;
            result |= r3 << 16;
            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline i32 readSignedInt(Packet& packet)
        {
            i32 r1, r2, r3, r4;
            i32 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);
            r3 = readByte(packet);
            r4 = readByte(packet);

            result |= r4 << 24;
            result |= r3 << 16;
            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline u64 readLong(Packet& packet)
        {
            u64 r1, r2, r3, r4,
                r5, r6, r7, r8;
            u64 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);
            r3 = readByte(packet);
            r4 = readByte(packet);
            r5 = readByte(packet);
            r6 = readByte(packet);
            r7 = readByte(packet);
            r8 = readByte(packet);

            result |= r8 << 56;
            result |= r7 << 48;
            result |= r6 << 40;
            result |= r5 << 32;
            result |= r4 << 24;
            result |= r3 << 16;
            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline int64_t readSignedLong(Packet& packet)
        {
            int64_t r1, r2, r3, r4,
                r5, r6, r7, r8;
            int64_t result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);
            r3 = readByte(packet);
            r4 = readByte(packet);
            r5 = readByte(packet);
            r6 = readByte(packet);
            r7 = readByte(packet);
            r8 = readByte(packet);

            result |= r8 << 56;
            result |= r7 << 48;
            result |= r6 << 40;
            result |= r5 << 32;
            result |= r4 << 24;
            result |= r3 << 16;
            result |= r2 << 8;
            result |= r1;

            return result;
        }

        static inline std::string readString(Packet& packet, int length)
        {
            std::string data;
            for (int i = 0; i < length; i++)
            {
                data += readByte(packet);
            }
            return data;
        }

        static inline std::string readMapleString(Packet& packet)
        {
            u16 length = readShort(packet);
            std::string str = readString(packet, length);
            return str;
        }

        static inline void writeByte(Packet& packet, byte data)
        {
            packet.push_back(data);
        }

        static inline void writeSByte(Packet& packet, char data)
        {
            packet.push_back(data);
        }

        static inline void writeShort(Packet& packet, u16 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
        }

        static inline void writeSignedShort(Packet& packet, i16 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
        }

        static inline void writeInt(Packet& packet, u32 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
            writeByte(packet, (data >> 16) & 0xFF);
            writeByte(packet, (data >> 24) & 0xFF);
        }

        static inline void writeSignedInt(Packet& packet, i32 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
            writeByte(packet, (data >> 16) & 0xFF);
            writeByte(packet, (data >> 24) & 0xFF);
        }

        static inline void writeLong(Packet& packet, u64 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
            writeByte(packet, (data >> 16) & 0xFF);
            writeByte(packet, (data >> 24) & 0xFF);
            writeByte(packet, (data >> 32) & 0xFF);
            writeByte(packet, (data >> 40) & 0xFF);
            writeByte(packet, (data >> 48) & 0xFF);
            writeByte(packet, (data >> 56) & 0xFF);
        }

        static inline void writeSignedLong(Packet& packet, int64_t data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
            writeByte(packet, (data >> 16) & 0xFF);
            writeByte(packet, (data >> 24) & 0xFF);
            writeByte(packet, (data >> 32) & 0xFF);
            writeByte(packet, (data >> 40) & 0xFF);
            writeByte(packet, (data >> 48) & 0xFF);
            writeByte(packet, (data >> 56) & 0xFF);
        }

        static inline void writeString(Packet& packet, std::string data)
        {
            if (data.size())
            {
                writeShort(packet, static_cast<short>(data.size()));
                for (byte c : data)
                {
                    writeByte(packet, c);
                }
            }
        }

        static inline void writeByteArray(Packet& packet, std::vector<byte> byteArray)
        {
            for (byte val : byteArray)
            {
                writeByte(packet, val);
            }
        }

        static inline std::stringstream outputShortHex(short packetShort)
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

        static inline std::stringstream outputByteHex(byte packetByte)
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

        static inline std::stringstream outputPacketHex(Packet packet)
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

        static inline std::stringstream outputPacketDec(Packet packet)
        {
            std::stringstream ss;
            for (byte val : packet)
            {
                ss << (int)val << ' ';
            }
            ss << std::dec;

            return ss;
        }

        static inline std::stringstream outputPacketString(Packet packet)
        {
            std::stringstream ss;
            for (byte val : packet)
            {
                ss << (char)val << ' ';
            }
            ss << std::dec;

            return ss;
        }
    };
}