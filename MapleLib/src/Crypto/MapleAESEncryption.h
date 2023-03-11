/*********************************************************************************
* AuroraSource - A C++ MapleStory Server Emulator
* Copyright(C) 2021 Duncan Bauer <duncanebauer@gmail.com>
*
* This program is free software : you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************************/

#ifndef MAPLEAESENCRYPTION_H
#define MAPLEAESENCRYPTION_H

// Maple Crypto
#include "MapleCryptoConstants.h"

// C++
#include <string>

// CryptoPP
#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

namespace MapleCrypto
{
    namespace AESEncryption
    {
        // Function prototypes
        std::string aesCrypt(ByteBuffer* _iv, ByteBuffer* _data, bool _cryptFlag);
        std::string aesCrypt(ByteBuffer* _iv, ByteBuffer* _data, bool _cryptFlag, const ByteBuffer* _key);

        inline std::string aesCrypt(ByteBuffer* _iv, ByteBuffer* _data, bool _cryptFlag)
        {
            const ByteBuffer key = Constants::getTrimmedUserKey();
            return aesCrypt(_iv, _data, _cryptFlag, &key);
        }

        inline std::string aesCrypt(ByteBuffer* _iv, ByteBuffer* _data, bool _cryptFlag, const ByteBuffer* _key)
        {
            CryptoPP::AutoSeededRandomPool randPool;
            CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

            CryptoPP::SecByteBlock key(_key->data(), CryptoPP::AES::MAX_KEYLENGTH);
            CryptoPP::SecByteBlock iv(_iv->data(), CryptoPP::AES::BLOCKSIZE);

            randPool.GenerateBlock(key, 32);
            randPool.GenerateBlock(iv, 16);

            std::string retVal;
            if(_cryptFlag)
            {
                try
                {
                    CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption e;
                    e.SetKeyWithIV(key, key.size(), iv);
                    CryptoPP::StringSource s(_data->data(), true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(retVal)));
                }
                catch(const CryptoPP::Exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    exit(1);
                }
            }
            else
            {
                try
                {
                    CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption d;
                    d.SetKeyWithIV(key, key.size(), iv);
                    CryptoPP::StringSource s(_data->data(), true, new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(retVal)));
                }
                catch(const CryptoPP::Exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    exit(1);
                }
            }
            
            return retVal;
        }
    };
};

#endif