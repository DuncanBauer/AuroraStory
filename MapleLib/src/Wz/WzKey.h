#pragma once

#include "Maple.h"

#include "../Net/MapleCrypto.h"

#include <plusaes/plusaes.hpp>
//#include <cryptopp/aes.h>
//#include <cryptopp/cryptlib.h>
//#include <cryptopp/modes.h>
//#include <cryptopp/osrng.h>

#include <iostream>

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

				std::cout << "WzKey Key: " << m_AESKey.data() << '\n';
				std::cout << "WzKey Key size: " << m_AESKey.size() << '\n';

			}

			WzKey& operator=(const WzKey& other)
			{
				m_AESKey = other.m_AESKey;
				m_Keys = other.m_Keys;
				m_IV = other.m_IV;
				return *this;
			}

			byte& operator[](int index)
			{
				if (m_Keys.empty() || m_Keys.size() <= index)
				{
					//EnsureKeySize(index + 1);
				}
				return m_Keys[index];
			}

			//void EnsureKeySize(int size)
			//{
			//	if (m_Keys.size() > size)
			//	{
			//		return;
			//	}

			//	size = (int)ceil(1.0 * size / m_BatchSize) * m_BatchSize;
			//	ByteBuffer newKeys(size);

			//	if (Util::BitTool::ToInt32(m_IV, 0) == 0)
			//	{
			//		m_Keys = newKeys;
			//		return;
			//	}

			//	int startIndex = 0;

			//	try
			//	{
			//		if (!m_Keys.empty())
			//		{
			//			std::memcpy(newKeys.data(), m_Keys.data(), m_Keys.size());
			//			startIndex = (int)(m_Keys.size());
			//		}

			//		CryptoPP::ECB_Mode<CryptoPP::Rijndael>::Encryption e;
			//		e.SetKeyWithIV(m_AESKey.data(), m_AESKey.size(), m_IV.data());

			//		size_t remaining = (size_t)size - startIndex;
			//		byte buffer[16] = { 0 };

			//		for (int i = 0; i < remaining; i += 16)
			//		{
			//			if (i == 0)
			//			{
			//				for (int j = 0; j < 16; j++)
			//				{
			//					buffer[j] = m_IV[j % 4];
			//				}
			//			}
			//			e.ProcessData(newKeys.data(), buffer, newKeys.size());
			//		}
			//		m_Keys = newKeys;
			//	}
			//	catch (std::exception e)
			//	{
			//		std::cout << e.what() << '\n';
			//	}
			//}

			static ByteBuffer GetIvFromZlz()
			{
				//std::ifstream zlzStream("ZLZ.dll");
				ByteBuffer iv(4);
				//zlzStream.seekg(0x10040);
				//zlzStream.read((char*)(iv.data()), 4);
			//	zlzStream.Seek(0x10040, SeekOrigin.Begin);
			//	zlzStream.Read(iv, 0, 4);
				return iv;
			}

			static ByteBuffer GetAesKeyFromZlz()
			{
				//std::ifstream zlzStream("ZLZ.dll");
				ByteBuffer aes(32);
				//zlzStream.seekg(0x10060);

				//for (int i = 0; i < 8; i++)
				//{
				//	zlzStream.read((char*)(aes.data()), 4);
				//	zlzStream.seekg(0x10060 + (i * 12));
				//}
			//	zlzStream.Seek(0x10060, SeekOrigin.Begin);
			//	for (int i = 0; i < 8; i++)
			//	{
			//		zlzStream.Read(aes, i * 4, 4);
			//		zlzStream.Seek(12, SeekOrigin.Current);
			//	}
				return aes;
			}

			static WzKey GenerateWzKey(ByteBuffer iv)
			{
				return WzKey(iv, ByteBuffer(Constants::GetTrimmedUserKey()));
			}

			static WzKey GenerateGMSWzKey()
			{
				return WzKey(ByteBuffer(Constants::WZ_GMS_IV, 
										Constants::WZ_GMS_IV + 4),
							 ByteBuffer(Constants::GetTrimmedUserKey()));
			}

			ByteBuffer m_AESKey;
			ByteBuffer m_Keys;
			ByteBuffer m_IV;
			int m_BatchSize = 4096;
		private:
	};
}