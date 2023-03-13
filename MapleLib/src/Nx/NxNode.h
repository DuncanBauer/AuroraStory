#pragma once

#include "Maple.h"
#include "NxFile.h"
#include "NxAudio.h"
#include "NxBitmap.h"

namespace Nx
{
	enum class NxDataType : uint16_t 
	{
		NONE = 0,
		INTEGER = 1,
		DOUBLE = 2,
		STRING = 3,
		VECTOR = 4,
		BITMAP = 5,
		AUDIO = 6,
	};

	struct AURORA_MAPLE_API NxAudioData
	{
		uint32_t index;
		uint32_t length;
	};

	struct AURORA_MAPLE_API NxBitmapData
	{
		uint32_t index;
		uint16_t width;
		uint16_t height;
	};

	class AURORA_MAPLE_API NxNodeData
	{
		public:
			uint32_t const name;
			uint32_t const children;
			uint16_t const num;
			NxDataType const type;
			union {
				int64_t const ireal;
				double const dreal;
				uint32_t const string;
				int32_t const vector[2];
				NxBitmapData const bitmap;
				NxAudioData const audio;
			};
	};

	class AURORA_MAPLE_API NxNode
	{
		public:
			//Constructors
			NxNode() = default;
			NxNode(NxNode const &);//Only reason this isn't defaulted is because msvc has issues
			
			NxNode & operator=(NxNode const &) = default;
			//These methods are primarily so nodes can be used as iterators and iterated over
			NxNode begin() const;
			NxNode end() const;
			NxNode operator*() const;
			NxNode & operator++();
			NxNode operator++(int);
			bool operator==(NxNode const &) const;
			bool operator!=(NxNode const &) const;
			bool operator<(NxNode const &) const;

			//This checks whether or not the node points to an actual node
			//Even if the node ends up being a null node, you can still use it safely
			//It'll just fall back to returning default values and more null nodes
			//However, if the file this node was obtained from was deleted
			//then the node becomes invalid and this operator cannot tell you that
			explicit operator bool() const;

			//Methods to access the children of the node by name
			//Note that the versions taking integers convert the integer to a string
			//They do not access the children by their integer index
			//If you wish to do that, use somenode.begin() + integer_index
			NxNode operator[](unsigned int) const;
			NxNode operator[](signed int) const;
			NxNode operator[](unsigned long) const;
			NxNode operator[](signed long) const;
			NxNode operator[](unsigned long long) const;
			NxNode operator[](signed long long) const;
			NxNode operator[](std::string const &) const;
			NxNode operator[](char const *) const;
			//This method uses the string value of the NxNode, not the node's name
			NxNode operator[](NxNode const &) const;

			//Operators to easily cast a node to get the data
			//Allows things like string s = somenode
			//Will automatically cast between data types as needed
			//For example if the node has an integer value but you want a string
			//then the operator will automatically convert the integer to a string
			operator unsigned char() const;
			operator signed char() const;
			operator unsigned short() const;
			operator signed short() const;
			operator unsigned int() const;
			operator signed int() const;
			operator unsigned long() const;
			operator signed long() const;
			operator unsigned long long() const;
			operator signed long long() const;
			operator float() const;
			operator double() const;
			operator long double() const;
			operator std::string() const;
			operator vector2i() const;
			operator NxBitmap() const;
			operator NxAudio() const;

			//Explicitly called versions of all the operators
			//When it takes a parameter, that is used as the default value
			//if a suitable data value cannot be found in the node
			int64_t GetInteger(int64_t = 0) const;
			double GetReal(double = 0) const;
			std::string GetString(std::string = "") const;
			vector2i GetVector(vector2i = {0, 0}) const;
			NxBitmap GetBitmap() const;
			NxAudio GetAudio() const;
			bool GetBool() const;
			bool GetBool(bool) const;
			//Returns the x and y coordinates of the vector data value
			int32_t GetX() const;
			int32_t GetY() const;
			//The name of the node
			std::string GetName() const;
			//The number of children in the node
			size_t GetSize() const;
			//Gets the type of data contained within the node
			NxDataType GetDataType() const;
			//Returns the root node of the file this node was derived from
			NxNode GetRoot() const;
			//Takes a '/' separated string, and resolves the given path
			NxNode Resolve(std::string) const;
		
		private:
			NxNode(NxNodeData const * data, NxFileData const * file);
			NxNode GetChild(char const *, uint16_t) const;
			int64_t ToInteger() const;
			double ToReal() const;
			std::string ToString() const;
			vector2i ToVector() const;
			NxBitmap ToBitmap() const;
			NxAudio ToAudio() const;
			
			//Internal variables
			NxNodeData const * m_Data = nullptr;
			NxFileData const * m_File = nullptr;

			friend class NxFile;
			friend class NxBitmap;
			friend class NxAudio;
	};
}