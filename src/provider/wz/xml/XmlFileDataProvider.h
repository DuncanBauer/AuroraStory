//#pragma once
//
//#include <filesystem>
//
//#include "provider/wz/WzDataProvider.h"
//
//namespace Provider
//{
//    class XmlFileDataProvider : public WzDataProvider
//    {
//    public:
//        XmlFileDataProvider() = delete;
//        XmlFileDataProvider(XmlFileDataProvider const&) = delete;
//        XmlFileDataProvider(std::filesystem::path file);
//
//        void* getData(std::string const& path) override;
//        void* getRoot() override;
//    };
//}