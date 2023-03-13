#pragma once

#include "WzObject.h"

#include "../Net/MapleCrypto.h"

#include <math.h>
#include <bit>
#include <sstream>

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/sha.h>

namespace Wz
{
	class WzHeader
	{
		public:
			void RecalculateFileStart()
			{
				m_FileStart = (unsigned int)(m_Ident.length() + sizeof(unsigned long) + sizeof(unsigned int) + m_Copyright.length() + 1);
			}
			WzHeader GetDefault()
			{
				WzHeader header;
				header.m_Ident = "PKG1";
				header.m_Copyright = "Package file v1.0 Copyright 2002 Wizet, ZMS";
				header.m_FileStart = 60;
				header.m_FileSize = 0;
				return header;
			}

		public:
			std::string m_Ident;
			std::string m_Copyright;
			unsigned int m_FileStart;
			unsigned long m_FileSize;
	};

	class WzKey
	{
		public:
			WzKey(ByteBuffer iv, ByteBuffer aeskey) : m_IV(iv), m_AESKey(aeskey) {}
			WzKey(ByteBuffer iv, byte* aeskey) : m_IV(iv), m_AESKey(aeskey) {}

			byte& operator[](int index)
			{
				if (m_Keys.empty() || m_Keys.size() <= index)
				{
					EnsureKeySize(index + 1);
				}
				return m_Keys[index];
			}

			int ToInt32(ByteBuffer bytes, int startIndex)
			{
				int value = 0;
				for (int i = 0; i < 4; i++)
				{
					value |= static_cast<int>(bytes[(size_t)startIndex + i]) << (i * 8);
				}
				return value;
			}

			void EnsureKeySize(int size)
			{
				if (m_Keys.size() > size)
				{
					return;
				}

				size = (int)ceil(1.0 * size / m_BatchSize) * m_BatchSize;
				ByteBuffer newKeys(size);

				if (ToInt32(m_IV, 0) == 0)
				{
					m_Keys = newKeys;
					return;
				}

				int startIndex = 0;

				if (!m_Keys.empty())
				{
					std::memcpy(newKeys.data(), m_Keys.data(), m_Keys.size());
					startIndex = m_Keys.size();
				}
				
				CryptoPP::ECB_Mode<CryptoPP::Rijndael>::Encryption e;
				e.SetKeyWithIV(m_AESKey.data(), m_AESKey.size(), m_IV.data());
				
				size_t remaining = (size_t)size - startIndex;
				byte buffer[16];

				for (int i = 0; i < remaining; i += 16)
				{
					if (i == 0)
					{
						for (int j = 0; j < 16; j++)
						{
							buffer[j] = m_IV[j % 4];
						}
					}
					e.ProcessData(newKeys.data(), buffer, newKeys.size());
				}
				m_Keys = newKeys;
			}

		private:
			ByteBuffer m_AESKey;
			ByteBuffer m_Keys;
			ByteBuffer m_IV;
			int m_BatchSize = 4096;
	};

	class WzKeyGenerator
	{

		static byte* GetIvFromZlz(std::string zlzStream)
		{
			byte iv[4];
			zlzStream.Seek(0x10040, SeekOrigin.Begin);
			zlzStream.Read(iv, 0, 4);
			return iv;
		}

		static byte* GetAesKeyFromZlz(FileStream zlzStream)
		{
			byte aes[32];
			zlzStream.Seek(0x10060, SeekOrigin.Begin);
			for (int i = 0; i < 8; i++)
			{
				zlzStream.Read(aes, i * 4, 4);
				zlzStream.Seek(12, SeekOrigin.Current);
			}
			return aes;
		}

		static WzKey GenerateWzKey(ByteBuffer iv)
		{
			return WzKey(iv, ByteBuffer(Net::Crypto::Constants::GetTrimmedUserKey()));
		}
	};

	class WzFile : public WzObject
	{

	};
}