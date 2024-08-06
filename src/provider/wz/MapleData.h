#pragma once

#include <string>
#include <vector>

#include "MapleDataEntity.h"
#include "nx/nx.h"
#include "nx/node.h"
#include "nx/audio.h"
#include "nx/bitmap.h"
#include "Typedefs.h"

namespace Provider
{
    class MapleDataType
    {
    public:
        static const u16 k_NONE = 0;
    };

    class NxMapleDataType : public MapleDataType
    {
    public:
        static const u16 k_INTEGER = 1;
        static const u16 k_DOUBLE = 2;
        static const u16 k_STRING = 3;
        static const u16 k_VECTOR = 4;
        static const u16 k_BITMAP = 5;
        static const u16 k_AUDIO = 6;
    };

    class WzMapleDataType : public MapleDataType
    {
    public:
        static const u16 k_IMG_0x00 = 1;
        static const u16 k_SHORT = 2;
        static const u16 k_INTEGER = 3;
        static const u16 k_FLOAT = 4;
        static const u16 k_DOUBLE = 5;
        static const u16 k_STRING = 6;
        static const u16 k_EXTENDED = 7;
        static const u16 k_PROPERTY = 8;
        static const u16 k_CANVAS = 9;
        static const u16 k_VECTOR = 10;
        static const u16 k_CONVEX = 11;
        static const u16 k_SOUND = 12;
        static const u16 k_UOL = 13;
        static const u16 k_UNKNOWN_TYPE = 14;
        static const u16 k_UNKNOWN_EXTENDED_TYPE = 15;
    };

    class MapleData : public MapleDataEntity
    {
        using DataType = u16;

    public:
        inline DataType getType() { return m_type; }
        inline std::vector<std::shared_ptr<MapleData>> getChildren() { return m_children; }
        inline std::shared_ptr<MapleData> getChildByPath(std::string path) 
        { 
            //return m_children[path];
        }
        inline std::shared_ptr<MapleData> getData() { return m_data; }

    private:
        DataType m_type;
        std::vector<std::shared_ptr<MapleData>> m_children;
        std::shared_ptr<MapleData> m_data;
    };
}