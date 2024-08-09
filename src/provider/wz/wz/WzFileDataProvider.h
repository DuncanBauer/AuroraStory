//#pragma once
//
//#include <filesystem>
//
//#include "provider/wz/WzDataProvider.h"
//
//namespace Provider
//{
//    class WzFileDataProvider : public WzDataProvider
//    {
//    public:
//        WzFileDataProvider()                          = delete;
//        WzFileDataProvider(WzFileDataProvider const&) = delete;
//        WzFileDataProvider(std::filesystem::path file);
//
//        void* getData(std::string const& path) override;
//        void* getRoot() override;
//
//    private:
//    };
//}