#pragma once

#include <string>
#include <vector>

#include "MapleConstants.h"
#include "DataEntity.h"
#include "Typedefs.h"

namespace Provider
{
    class Data : public DataEntity
    {
        using MapleDataType = u16;

    public:
        Data() = default;
        Data(std::string name) : DataEntity(name) {}

        inline void                               setType(u16 type)                 { m_type = type; }
        inline MapleDataType                      getType()                         { return m_type; }
        inline std::vector<std::shared_ptr<Data>> getChildren()                     { return m_children; }
               std::shared_ptr<Data>              getChildByPath(std::string path);

    protected:
        MapleDataType                      m_type = WZDataType::k_NONE;
        std::vector<std::shared_ptr<Data>> m_children;
    };


    class IntData : public Data
    {
    public: 
        IntData()                     = delete;
        IntData(IntData const& other) = delete;
        IntData(IntData&& other)      = delete;

        IntData(u32 data) : m_data(data)                               { setType(WZDataType::k_INTEGER); }
        IntData(std::string name, u32 data) : Data(name), m_data(data) { setType(WZDataType::k_INTEGER); }

        inline u32 getData() { return m_data; }

    private:
        u32 m_data;
    };


    class DoubleData : public Data
    {
    public:
        DoubleData()                        = delete;
        DoubleData(DoubleData const& other) = delete;
        DoubleData(DoubleData&& other)      = delete;

        DoubleData(double data) : m_data(data)                               { setType(WZDataType::k_DOUBLE); }
        DoubleData(std::string name, double data) : Data(name), m_data(data) { setType(WZDataType::k_DOUBLE); }

        inline double getData() { return m_data; }

    private:
        double m_data;
    };


    class StringData : public Data
    {
    public:
        StringData()                        = delete;
        StringData(StringData const& other) = delete;
        StringData(StringData&& other)      = delete;

        StringData(std::string data) : m_data(data)                               { setType(WZDataType::k_STRING); }
        StringData(std::string name, std::string data) : Data(name), m_data(data) { setType(WZDataType::k_STRING); }

        inline std::string getData() { return m_data; }

    private:
        std::string m_data;
    };


    class VectorData : public Data
    {
        using vector = std::pair<i32, i32>;

    public:
        VectorData()                        = delete;
        VectorData(VectorData const& other) = delete;
        VectorData(VectorData && other)     = delete;

        VectorData(i32 x, i32 y) : m_data(x, y)                                 { setType(WZDataType::k_VECTOR); }
        VectorData(vector data)  : m_data(data)                                 { setType(WZDataType::k_VECTOR); }
        VectorData(std::string name, i32 x, i32 y) : Data(name), m_data(x, y)   { setType(WZDataType::k_VECTOR); }
        VectorData(std::string name, vector data) : Data(name), m_data(data)    { setType(WZDataType::k_VECTOR); }

        inline vector getData() { return m_data; }

    private:
        vector m_data;
    };
}