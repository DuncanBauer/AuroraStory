#pragma once

#include "Maple.h"

#include "../Wz/WzFile.h"
#include "../Wz/WzDirectory.h"
#include "../Wz/WzEnums.h"

#include <algorithm>
#include <filesystem>
#include <map>
#include <string>

namespace Util
{
	class WzTool
	{
		public:
			static std::map<std::string, int> StringCache;

			static unsigned int RotateLeft(unsigned int x, byte n)
			{
				return (unsigned int)(((x) << (n)) | ((x) >> (32 - (n))));
			}

			static unsigned int RotateRight(unsigned int x, byte n)
			{
				return (unsigned int)(((x) >> (n)) | ((x) << (32 - (n))));
			}

			static int GetCompressedIntLength(int i)
			{
				if (i > 127 || i < -127)
					return 5;
				return 1;
			}

			static int GetEncodedStringLength(std::string s)
			{
				int len = 0;
				if (s.empty())
					return 1;
				bool unicode = false;
				for(char c: s)
					if (c > 255)
						unicode = true;
				if (unicode)
				{
					if (s.size() > 126)
						len += 5;
					else
						len += 1;
					len += (int)(s.size()) * 2;
				}
				else
				{
					if (s.size() > 127)
						len += 5;
					else
						len += 1;
					len += (int)(s.size());
				}
				return len;
			}

			static int GetWzObjectValueLength(std::string s, byte type)
			{
				std::string storeName = type + "_" + s;
				if (s.size() > 4 && StringCache.contains(storeName))
				{
					return 5;
				}
				else
				{
					StringCache[storeName] = 1;
					return 1 + GetEncodedStringLength(s);
				}
			}

			//static T StringToEnum<T>(std::string name)
			//{
			//	try
			//	{
			//		return (T)Enum.Parse(typeof(T), name);
			//	}
			//	catch
			//	{
			//		return default(T);
			//	}
			//}

			static const byte* GetIvByMapleVersion(Wz::WzMapleVersion ver)
			{
				switch (ver)
				{
					case Wz::WzMapleVersion::EMS:
						return Net::Crypto::Constants::WZ_MSEA_IV;//?
					case Wz::WzMapleVersion::GMS:
						return Net::Crypto::Constants::WZ_GMS_IV;
					case Wz::WzMapleVersion::BMS:
					case Wz::WzMapleVersion::CLASSIC:
					default:
						return new byte[4];
				}
			}

			static int GetRecognizedCharacters(std::string source)
			{
				int result = 0;
				for(char c: source)
					if (0x20 <= c && c <= 0x7E)
						result++;
				return result;
			}

			static double GetDecryptionSuccessRate(std::string wzPath, Wz::WzMapleVersion encVersion, short version)
			{
				Wz::WzFile* wzf;
				if (version)
				{
					wzf = new Wz::WzFile(wzPath, encVersion);
				}
				else
				{
					wzf = new Wz::WzFile(wzPath, (short)version, encVersion);
				}
			
				wzf->ParseWzFile();
				if (version)
				{
					version = wzf->GetVersion();
				}
			
				int recognizedChars = 0;
				int totalChars = 0;
				for(Wz::WzDirectory wzdir: wzf->GetDirectory()->GetSubDirs())
				{
					recognizedChars += GetRecognizedCharacters(wzdir.GetName());
					totalChars += (int)(wzdir.GetName().size());
				}

				for(Wz::WzImage wzimg: wzf->GetDirectory()->GetImages())
				{
					recognizedChars += GetRecognizedCharacters(wzimg.GetName());
					totalChars += (int)(wzimg.GetName().size());
				}
				return (double)recognizedChars / (double)totalChars;
			}

			static Wz::WzMapleVersion DetectMapleVersion(std::string wzFilePath, short fileVersion)
			{
				std::map<Wz::WzMapleVersion, double> mapleVersionSuccessRates;
				short version = 0;
				mapleVersionSuccessRates.emplace(Wz::WzMapleVersion::GMS, GetDecryptionSuccessRate(wzFilePath, Wz::WzMapleVersion::GMS, version));
				mapleVersionSuccessRates.emplace(Wz::WzMapleVersion::EMS, GetDecryptionSuccessRate(wzFilePath, Wz::WzMapleVersion::EMS, version));
				mapleVersionSuccessRates.emplace(Wz::WzMapleVersion::BMS, GetDecryptionSuccessRate(wzFilePath, Wz::WzMapleVersion::BMS, version));
		
				fileVersion = (short)version;
				Wz::WzMapleVersion mostSuitableVersion = Wz::WzMapleVersion::GMS;
				double maxSuccessRate = 0;
				for(auto const& mapleVersionEntry: mapleVersionSuccessRates)
					if (mapleVersionEntry.second> maxSuccessRate)
					{
						mostSuitableVersion = (Wz::WzMapleVersion)mapleVersionEntry.first;
						maxSuccessRate = (double)mapleVersionEntry.second;
					}
				if (maxSuccessRate < 0.7 && std::filesystem::exists(wzFilePath + "ZLZ.dll"))
				{
					return Wz::WzMapleVersion::GETFROMZLZ;
				}
				else
				{
					return mostSuitableVersion;
				}
			}

			//const int WzHeader = 0x31474B50; //PKG1
			//static bool IsListFile(std::string path)
			//{
			//	BinaryReader reader = new BinaryReader(File.OpenRead(path));
			//	bool result = reader.ReadInt32() != WzHeader;
			//	reader.Close();
			//	return result;
			//}

			static ByteBuffer Combine(ByteBuffer a, ByteBuffer b)
			{
				ByteBuffer result;
				result.insert(result.end(), a.begin(), a.end());
				result.insert(result.end(), b.begin(), b.end());
				return result;
			}
		};
}
