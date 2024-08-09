#include "NxAudio.h"
#include "NxBitmap.h"
#include "NxFile.h"
#include "NxNode.h"

namespace Provider
{
    NxNode::NxNode(NxNodeData const* nodeData, NxFileData const* fileData) : m_data(nodeData), m_fileData(fileData)
    {}

    NxNode NxNode::begin() const
    {
        if (!m_data)
        {
            return { nullptr, m_fileData };
        }
        return { m_fileData->m_nodeTable + m_data->m_children, m_fileData };
    }

    NxNode NxNode::end() const
    {
        if (!m_data)
        {
            return { nullptr, m_fileData };
        }
        return { m_fileData->m_nodeTable + m_data->m_children + m_data->m_childCount, m_fileData };
    }

    NxNode& NxNode::operator++()
    {
        ++m_data;
        return *this;
    }

    std::string NxNode::getName() const
    {
        if (!m_data)
        {
            return {};
        }

        auto s = reinterpret_cast<char const*>(m_fileData->m_base) + m_fileData->m_stringTable[m_data->m_name];
        return { s + 2, *reinterpret_cast<u16 const*>(s) };
    }

    NxNodeType NxNode::getDataType() const
    {
        return m_data->m_nodeType;
    }

    //! Only gets an immediate child of the current node
    NxNode NxNode::getChild(std::string desiredChild) const
    {
        if (!m_data) 
        {
            return { nullptr, m_fileData };
        }

              auto currentChildPtr     = m_fileData->m_nodeTable + m_data->m_children;      // Pointer to current child
              auto remainingChildCount = m_data->m_childCount;                              // Remaining number of children
        const auto basePointer         = reinterpret_cast<const char*>(m_fileData->m_base); // Base pointer for nodes
        const auto stringTable         = m_fileData->m_stringTable;                         // Pointer to the string table
        const auto pathLength          = desiredChild.length();                             // Length of the input path

        while (true)
        {
            // Return if there are no children
            if (!remainingChildCount)
            {
                return { nullptr, m_fileData };
            }

            const auto halfChildCount      = static_cast<decltype(remainingChildCount)>(remainingChildCount >> 1);
            const auto midChildPtr         = currentChildPtr + halfChildCount;
            const auto currChildNameLoc    = basePointer + stringTable[midChildPtr->m_name];
            const auto currChildNameLength = *reinterpret_cast<std::uint16_t const*>(currChildNameLoc);       // Length of the string
            const auto currChildName       = reinterpret_cast<std::uint8_t const*>(currChildNameLoc + 2);     // Pointer to the child string
            const auto pathString          = reinterpret_cast<std::uint8_t const*>(desiredChild.data());  // Pointer to the input path
            const auto comparisonLength    = currChildNameLength < pathLength ? currChildNameLength : pathLength; // Length to compare
                  bool isAdjusted          = false;

            for (u32 i = 0; i < comparisonLength; ++i)
            {
                // Adjust search to the left half
                if (currChildName[i] > pathString[i])
                {
                    remainingChildCount = halfChildCount;
                    isAdjusted = true;
                    break;
                }
                // Adjust search to the right half
                else if (currChildName[i] < pathString[i])
                {
                    currentChildPtr = midChildPtr + 1; 
                    remainingChildCount -= halfChildCount + 1;
                    isAdjusted = true;
                    break;
                }
            }

            // Continue the loop to adjust search parameters
            if (isAdjusted)
            {
                continue; 
            }
            // Adjust for the right half
            else if (currChildNameLength < pathLength)
            {
                currentChildPtr = midChildPtr + 1;
                remainingChildCount -= halfChildCount + 1;
            }
            // Adjust for the left half
            else if (currChildNameLength > pathLength)
            {
                remainingChildCount = halfChildCount;
            }
            // Found the matching child
            else
            {
                return { midChildPtr, m_fileData };
            }
        }
    }

    std::int64_t NxNode::getInt(std::int64_t def) const
    {
        if (!m_data)
        {
            return def;
        }

        switch (m_data->m_nodeType)
        {
        case NxNodeType::NX_INT:
            return toInt();
        case NxNodeType::NX_DOUBLE:
            return static_cast<std::int64_t>(toDouble());
        case NxNodeType::NX_STRING:
            return std::stoll(toString());
        default:
            return def;
        }
    }

    double NxNode::getDouble(double def) const
    {
        if (!m_data)
        {
            return def;
        }

        switch (m_data->m_nodeType)
        {
        case NxNodeType::NX_INT:
            return static_cast<double>(toInt());
        case NxNodeType::NX_DOUBLE:
            return toDouble();
        case NxNodeType::NX_STRING:
            return std::stod(toString());
        default:
            return def;
        }
    }

    std::string NxNode::getString(std::string def) const
    {
        if (!m_data)
        {
            return def;
        }

        switch (m_data->m_nodeType)
        {
        case NxNodeType::NX_INT:
            return std::to_string(toInt());
        case NxNodeType::NX_DOUBLE:
            return std::to_string(toDouble());
        case NxNodeType::NX_STRING:
            return toString();
        default:
            return def;
        }
    }

    vector NxNode::getVector(vector def) const
    {
        if (m_data && m_data->m_nodeType == NxNodeType::NX_VECTOR)
        {
            return toVector();
        }
        return def;
    }

    NxBitmap NxNode::getBitmap() const
    {
        if (m_data && m_data->m_nodeType == NxNodeType::NX_BITMAP && m_fileData->m_header->m_bitmapCount)
        {
            return toBitmap();
        }
        return { nullptr, 0, 0 };
    }

    NxAudio NxNode::getAudio() const
    {
        if (m_data && m_data->m_nodeType == NxNodeType::NX_AUDIO && m_fileData->m_header->m_audioCount)
        {
            return toAudio();
        }
        return { nullptr, 0 };
    }

    std::string NxNode::toString() const
    {
        const auto s = reinterpret_cast<char const*>(m_fileData->m_base) + m_fileData->m_stringTable[m_data->m_string];
        return { s + 2, *reinterpret_cast<u16 const*>(s) };
    }

    NxBitmap NxNode::toBitmap() const
    {
#ifndef NDEBUG
        auto bitmap_offset = m_fileData->m_bitmapTable[m_data->m_bitmap.index];
        if (bitmap_offset % 8 != 0)
        {
            std::cerr << "[NX format error] Bitmap in file mapped to "
                << m_fileData->m_base
                << " is at offset "
                << bitmap_offset
                << ", which is not a multiple of 8\n";
        }

        return { reinterpret_cast<char const*>(m_fileData->m_base) + bitmap_offset,
                m_data->m_bitmap.width,
                m_data->m_bitmap.height };
#else
        return { reinterpret_cast<char const*>(m_fileData->m_base) + m_fileData->m_bitmapTable[m_data->m_bitmap.index],
                m_data->m_bitmap.width,
                m_data->m_bitmap.height };
#endif
    }

    NxAudio NxNode::toAudio() const
    {
        return { reinterpret_cast<char const*>(m_fileData->m_base) + m_fileData->m_audioTable[m_data->m_audio.index],
                m_data->m_audio.length };
    }

    //! Gets a child by path (Including non-immediate child nodes)
    NxNode NxNode::resolve(std::string path) const noexcept
    {
        std::size_t i      = 0;
        std::size_t last_i = 0;
        NxNode currentNode = *this;
        while (i < path.length()) 
        {
            if (path[i] == '/') 
            {
                currentNode = currentNode[path.substr(last_i, i - last_i)];
                ++i;
                last_i = i;
            }
            else 
            {
                ++i;
            }
        }

        currentNode = currentNode[path.substr(last_i, i - last_i)];
        return currentNode;
    }
}