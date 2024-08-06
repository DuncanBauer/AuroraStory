#include <filesystem>

#include "DataProviderFactory.h"
#include "WzFile.h"
#include "NxWzFile.h"
#include "XmlWzFile.h"
#include "util/LoggingTool.h"

namespace Provider
{
    DataProvider DataProviderFactory::getWZ(std::filesystem::path file) 
    {
        if (file.string().ends_with("nx"))
        {
            try
            {
                return NxWzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading NX File failed: {}", e.what());
            }
        }
        else if (file.string().ends_with("wz") && !std::filesystem::is_directory(file))
        {
            try 
            {
                //return WzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading WZ File failed: {}", e.what());
            }
        }
        else 
        {
            try
            {
                //return XmlWzFile(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading XML File failed: {}", e.what());
            }
        }
    }

    DataProvider DataProviderFactory::getDataProvider(const std::string& fileIn) 
    {
        return getWZ(fileIn);
    }

    std::filesystem::path DataProviderFactory::fileInWZPath(std::string filename)
    {
        std::filesystem::path file(m_wzPath + filename);
        if (std::filesystem::exists(file))
        {
            return file;
        }

        return;
    }
}