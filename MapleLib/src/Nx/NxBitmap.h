//#pragma once
//
//#include "Maple.h"
//
//#include "lz4.h"
//#include <vector>
//
//namespace Nx
//{
//	class NxNode;
//
//	class AURORA_MAPLE_API NxBitmap
//	{
//		public:
//			//Comparison operators, useful for containers
//			bool operator==(NxBitmap const & other) const { return m_Data == other.m_Data; }
//			bool operator<(NxBitmap const & other) const { return m_Data < other.m_Data; }
//
//			//Returns whether the NxBitmap is valid or merely null
//			explicit operator bool() const { return m_Data ? true : false; }
//
//			//This function decompresses the data on the fly
//			//Do not free the pointer returned by this method
//			//Every time this function is called
//			//any previous pointers returned by this method become invalid
//			mutable std::vector<char> m_BitmapBuffer;
//			void const * GetData() const
//			{
//				if(!m_Data)
//				{
//					return nullptr;
//				}
//
//				auto const length = GetLength();
//				if (static_cast<unsigned long long>(length) + 0x20 > m_BitmapBuffer.size())
//				{
//					m_BitmapBuffer.resize(static_cast<std::vector<char, std::allocator<char>>::size_type>(length) + 0x20);
//				}
//				
//				// Skip the 'PKG4' at the beginning of the file
//				::LZ4_decompress_fast(4 + reinterpret_cast<char const *>(m_Data), m_BitmapBuffer.data(), static_cast<int>(length));
//				return m_BitmapBuffer.data();
//			}
//			uint16_t GetWidth() const { return m_Width; }
//			uint16_t GetHeight() const { return m_Height;}
//			uint32_t GetLength() const { return 4u * m_Width * m_Height; }
//			size_t GetId() const { return reinterpret_cast<size_t>(m_Data); } //Returns a unique id, useful for keeping track of what NxBitmap you loaded
//
//		private:
//			NxBitmap(void const * data, uint16_t width, uint16_t height) : m_Data(data), m_Width(width), m_Height(height) {}
//			void const * m_Data = nullptr;
//			uint16_t m_Width,
//							 m_Height = 0;
//			friend class NxNode;
//	};
//}