#include "NxWzFile.h"
#include "util/LoggingTool.h"

namespace Provider
{
    //NxWzFile::NxWzFile(std::filesystem::path file)
    //{
    //    root = fileIn;
    //    rootForNavigation = new WZDirectoryEntry(fileIn.getName(), 0, 0, null);
    //    fillMapleDataEntitys(root, rootForNavigation);
    //}

    //void NxWzFile::fillMapleDataEntitys(std::filesystem::path file, WZDirectoryEntry wzdir) 
    //{
    //    for (File file : file.listFiles()) {
    //        String fileName = file.getName();
    //        if (file.isDirectory() && !fileName.endsWith(".img")) {
    //            WZDirectoryEntry newDir = new WZDirectoryEntry(fileName, 0, 0, wzdir);
    //            wzdir.addDirectory(newDir);
    //            fillMapleDataEntitys(file, newDir);
    //        }
    //        else if (fileName.endsWith(".xml")) {
    //            wzdir.addFile(new WZFileEntry(fileName.substring(0, fileName.length() - 4), 0, 0, wzdir));
    //        }
    //    }
    //}

    //Data NxWzFile::getData(std::string path) override
    //{

    //}
}