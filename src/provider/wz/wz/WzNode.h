//#pragma once
//
//#include "Typedefs.h"
//
//namespace Provider
//{
//    enum class WzNodeType : u8 
//    { 
//        WZ_NONE   = 0,
//        WZ_INT    = 1,
//        WZ_DOUBLE = 2,
//        WZ_STRING = 3,
//        WZ_UOL    = 4,
//        WZ_SPRITE = 5,
//        WZ_SOUND  = 6,
//        WZ_IMG    = 7
//    };
//
//    class WzNodeData 
//    {
//    public:
//        union vt 
//        {
//            double m_dreal;
//            u32    m_ireal;
//            char*  m_string;
//            Img*   m_img;
//        };
//
//        WzNodeData* m_parent;
//        char*       m_name;
//        WzNodeData* m_children;
//        uint16_t    m_num;
//
//    private:
//        WzNodeData(const WzNodeData& other);
//    };
//
//    class WzNode
//    {
//    public:
//    private:
//        WzNodeData* m_data;
//    };
//}