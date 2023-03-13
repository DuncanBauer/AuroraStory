#pragma once

#include "Maple.h"

namespace Nx
{
	class NxNode;

	class AURORA_MAPLE_API NxAudio
	{
		public:
			//Comparison operators, useful for containers
			bool operator==(NxAudio const & other) const { return m_Data == other.m_Data; }
			bool operator<(NxAudio const & other) const { return m_Data < other.m_Data; }

			//Returns whether the NxAudio is valid or merely null
			explicit operator bool() const { return m_Data ? true : false; }

			//Does not do any sort of decompression
			//Do not free the pointer returned by this method
			//The pointer remains valid until the file this NxAudio is part of is destroyed
			void const * GetData() const { return m_Data; }
			uint32_t GetLength() const { return m_Length; }
			size_t GetId() const {	return reinterpret_cast<size_t>(m_Data); } //Returns a unique id, useful for keeping track of what NxAudio you loaded

		private:
			NxAudio(void const * data, uint32_t length) : m_Data(data), m_Length(length) {}
			void const * m_Data = nullptr;
			uint32_t m_Length = 0;
			friend class NxNode;
	};
}