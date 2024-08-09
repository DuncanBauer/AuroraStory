#include <filesystem>

#include "DataProviderFactory.h"
#include "nx/NxFileDataProvider.h"
#include "wz/WzFileDataProvider.h"
#include "xml/XmlFileDataProvider.h"
#include "util/LoggingTool.h"

namespace Provider
{
    std::shared_ptr<WzDataProvider> DataProviderFactory::getWZ(std::filesystem::path file)
    {
        if (file.string().ends_with("nx"))
        {
            try
            {
                return std::make_shared<NxFileDataProvider>(file);
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
                //return WzFileDataProvider(file);
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
                //return XmlFileDataProvider(file);
            }
            catch (std::exception e)
            {
                SERVER_ERROR("Loading XML File failed: {}", e.what());
            }
        }

        return std::shared_ptr<WzDataProvider>();
    }

    std::shared_ptr<WzDataProvider> DataProviderFactory::getDataProvider(std::string const& filename)
    {
        std::filesystem::path file;

        // Check if the directory exists
        if (!std::filesystem::exists(m_wzPath) || !std::filesystem::is_directory(m_wzPath))
        {
            SERVER_ERROR("WZ directory does not exist.");
            throw;
        }

        // Iterate through the directory and find the file
        bool fileFound = false;
        for (std::filesystem::directory_entry const& entry : std::filesystem::directory_iterator(m_wzPath))
        {
            // Exclude any folders/links/special files?
            if (entry.is_regular_file())
            {
                // Check if the file name matches (without considering the extension)
                if (entry.path().stem() == filename)
                {
                    std::cout << "Found file: " << entry.path() << "\n";
                    file = entry.path();
                    fileFound = true;
                    break;
                }
            }
        }

        if (!fileFound)
        {
            SERVER_ERROR("Missing {} provider file.", filename);
            throw;
        }

        return getWZ(file);
    }
}