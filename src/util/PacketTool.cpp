#include <iomanip>
#include <sstream>
#include <vector>

#include "PacketTool.h"

namespace util
{
    namespace PacketTool
    {
        byte readByte(Packet& packet)
        {
            byte result = packet.front();
            packet.erase(packet.begin());
            return result;
        }

        u16 readShort(Packet& packet)
        {
            u16 r1, r2;
            u16 result = 0;

            r1 = readByte(packet);
            r2 = readByte(packet);

            result |= r2 << 8;
            result |= r1;

            return result;
        }

        u32 readInt(Packet& packet)
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
        
        u64 readLong(Packet& packet)
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

        std::string readString(Packet& packet, int length)
        {
            std::string data;
            for (int i = 0; i < length; i++)
            {
                data += readByte(packet);
            }
            return data;
        }
        
        std::string readMapleString(Packet& packet)
        {
            u16 length = readShort(packet);
            std::string str = readString(packet, length);
            return str;
        }

        void writeByte(Packet& packet, byte data)
        {
            packet.push_back(data);
        }

        void writeShort(Packet& packet, u16 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
        }

        void writeInt(Packet& packet, u32 data)
        {
            writeByte(packet, data & 0xFF);
            writeByte(packet, (data >> 8) & 0xFF);
            writeByte(packet, (data >> 16) & 0xFF);
            writeByte(packet, (data >> 24) & 0xFF);
        }

        void writeIntAsByte(Packet& packet, u32 data)
        {
            writeByte(packet, (byte)data);
        }

        void writeLong(Packet& packet, u64 data)
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

        void writeString(Packet& packet, std::string data)
        {
            for (byte c : data)
            {
                writeByte(packet, c);
            }
        }

        void writeMapleString(Packet& packet, std::string data)
        {
            writeShort(packet, static_cast<short>(data.size()));
            writeString(packet, data);
        }

        void writeByteArray(Packet& packet, std::vector<byte> byteArray)
        {
            for (byte val : byteArray)
            {
                writeByte(packet, val);
            }
        }

        std::stringstream outputShortHex(short packetShort)
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

        std::stringstream outputByteHex(byte packetByte)
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

        //std::stringstream outputPacketHex(Packet packet)
        //{
        //    std::stringstream ss;
        //    for (byte val : packet)
        //    {
        //        ss << "0x"
        //           << std::uppercase    // Print letters in uppercase (A-F)
        //           << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
        //           << std::setfill('0') // Fill with zeroes if necessary
        //           << std::hex
        //           << (int)(val & 0xFF)
        //           << ' ';
        //    }
        //    ss << std::dec;
        //    return ss;
        //}

        std::stringstream outputPacketHex(Packet packet)
        {
            std::stringstream ss;
            for (byte val : packet)
            {
                ss << std::hex
                    << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
                    << std::setfill('0') // Fill with zeroes if necessary
                    << (int)(val)
                    << ' ';
            }
            ss << std::dec;

            return ss;
        }

        std::stringstream outputByteBufferHex(byte* buffer, size_t size)
        {
            std::stringstream ss;
            for (int i = 0; i < size; i++)
            {
                ss << std::hex
                    << std::setw(2)      // Set width to 2 characters (for a byte)<< val << ' ';
                    << std::setfill('0') // Fill with zeroes if necessary
                    << (int)(buffer[i])
                    << ' ';
            }
            ss << std::dec;

            return ss;
        }

        std::stringstream outputPacketDec(Packet packet)
        {
            std::stringstream ss;
            for (byte val : packet)
            {
                ss << (int)val << ' ';
            }
            ss << std::dec;

            return ss;
        }

        std::stringstream outputPacketString(Packet packet)
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
}