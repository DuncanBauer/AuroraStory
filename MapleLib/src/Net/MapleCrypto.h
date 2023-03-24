#pragma once

// Project headers
#include "Maple.h"
#include "../Util/BitTool.h"

// C++ headers

// Third party headers
#include <plusaes/plusaes.hpp>

namespace Net
{
    namespace Crypto
    {
        // MAPLE CUSTOM ENCRYPTION
        static void MapleEncrypt(ByteBuffer& data)
        {
            size_t j;
            int length = data.size();
            byte a;
            byte c;

            for (size_t i = 0; i < 3; ++i)
            {
                a = 0;
                for (j = length; j > 0; j--)
                {
                    c = data[length - j];
                    c = Util::BitTool::RollLeft(c, 3);
                    c = (byte)(c + j);
                    c ^= a;
                    a = c;
                    c = Util::BitTool::RollRight(a, j);
                    c ^= 0xFF;
                    c += 0x48;
                    data[length - j] = c;
                }
                a = 0;

                for (j = length; j > 0; --j)
                {
                    c = data[j - 1];
                    c = Util::BitTool::RollLeft(c, 4);
                    c = (byte)(c + j);
                    c ^= a;
                    a = c;
                    c ^= 0x13;
                    c = Util::BitTool::RollRight(c, 3);
                    data[j - 1] = c;
                }
            }
        }
                
        static void MapleDecrypt(ByteBuffer& data)
        {
            size_t j;
            int length = data.size();
            byte a;
            byte b;
            byte c;
                    
            for (size_t i = 0; i < 3; ++i)
            {
                a = 0;
                b = 0;
                for (j = length; j > 0; --j)
                {
                    c = data[j - 1];
                    c = Util::BitTool::RollLeft(c, 3);
                    c ^= 0x13;
                    a = c;
                    c ^= b;
                    c = (byte)(c - j);
                    c = Util::BitTool::RollRight(c, 4);
                    b = a;
                    data[j - 1] = c;
                }
                a = 0;
                b = 0;
                        
                for (j = length; j > 0; --j)
                {
                    c = data[length - j];
                    c -= 0x48;
                    c ^= 0xFF;
                    c = Util::BitTool::RollLeft(c, j);
                    a = c;
                    c ^= b;
                    c = (c - j);
                    c = Util::BitTool::RollRight(c, 3);
                    b = a;
                    data[length - j] = c;
                }
            }
        }
    }
};