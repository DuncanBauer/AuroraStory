#pragma once

#include "Maple.h"

#include "../Net/MapleCrypto.h"

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>

namespace Wz
{
	class AURORA_MAPLE_API WzKey
	{
		public:
			WzKey() {}
			WzKey(ByteBuffer iv, ByteBuffer aeskey) : m_IV(iv), m_AESKey(aeskey) {}
			WzKey(const WzKey& other)
			{
				m_AESKey = other.m_AESKey;
				m_Keys = other.m_Keys;
				m_IV = other.m_IV;
			}

			WzKey& operator=(const WzKey& other)
			{
				m_AESKey = other.m_AESKey;
				m_Keys = other.m_Keys;
				m_IV = other.m_IV;
			}

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
				byte buffer[16] = { 0 };

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

			static byte* GetIvFromZlz(std::string zlzStream)
			{
			//	byte iv[4];
			//	zlzStream.Seek(0x10040, SeekOrigin.Begin);
			//	zlzStream.Read(iv, 0, 4);
			//	return iv;
			}

			static byte* GetAesKeyFromZlz()//FileStream zlzStream)
			{
			//	byte aes[32];
			//	zlzStream.Seek(0x10060, SeekOrigin.Begin);
			//	for (int i = 0; i < 8; i++)
			//	{
			//		zlzStream.Read(aes, i * 4, 4);
			//		zlzStream.Seek(12, SeekOrigin.Current);
			//	}
			//	return aes;
			}

			static WzKey GenerateWzKey(ByteBuffer iv)
			{
				return WzKey(iv, ByteBuffer(Net::Crypto::Constants::GetTrimmedUserKey()));
			}

		private:
			ByteBuffer m_AESKey;
			ByteBuffer m_Keys;
			ByteBuffer m_IV;
			int m_BatchSize = 4096;
	};
}