#pragma once

#include "Maple.h"

#include "WzObject.h"

#include "WzBinaryReader.h"


namespace Wz
{
	class WzImageProperty;
	using WzImageProperties = std::vector<WzImageProperty>;
	class AURORA_MAPLE_API WzImage : public WzObject
	{
		public:
			WzImage();
			~WzImage();

			// Image methods
			void SaveImage();
			void Delete();
			void ParseImage();
			void UnparseImage();
			virtual void ExportXML();

			// Property methods
			void AddProperty(WzImageProperty prop);
			void DeleteProperty(WzImageProperty prop);
			void AddProperties(WzImageProperties props);
			void DeleteProperties(WzImageProperties props);
			void ClearProperties();

			// Getters and Setters
			bool IsParsed() const { return m_Parsed; }
			bool IsChanged() const { return m_Changed; }
			bool IsParsingEverything() const { return m_ParseEverything; }
			int GetSize() const { return m_Size; }
			int GetChecksum() const { return m_Checksum; }
			int GetBlockStart() const { return m_BlockStart; }
			unsigned int GetOffset() const { return m_Offset; }
			long GetTempFileStart() const { return m_TempFileStart; }
			long GetTempFileEnd() const { return m_TempFileEnd; }
			WzBinaryReader& GetReader() { return *m_Reader; }
			WzImageProperties& GetProperties() { return *m_Properties; }

			//void Set(int size) { m_Size = size; }
			//void Set(int checksum) { m_Checksum = checksum; }
			//void Set(int blockStart) { m_BlockStart = blockStart; }
			//void Set(unsigned int offset) { m_Offset = offset; }
			//void Set(long tempFileStart) { m_TempFileStart = tempFileStart; }
			//void SetT(long tempFileEnd) { m_TempFileEnd = tempFileEnd; }
			//void SetParsedState(bool parsed) { m_Parsed = parsed; }
			//void SetChangedState(bool changed) { m_Changed = changed; }
			//void SetParseEverythingState(bool parseEverything) { m_ParseEverything = parseEverything; }

		private:
			bool m_Parsed;
			bool m_Changed;
			bool m_ParseEverything;

			int m_Size;
			int m_Checksum;
			int m_BlockStart;
			unsigned int m_Offset;
			long m_TempFileStart;
			long m_TempFileEnd;

			WzBinaryReader* m_Reader;
			WzImageProperties* m_Properties;
	};
}