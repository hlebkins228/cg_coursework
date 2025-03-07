#ifndef READER_H_

#define READER_H_

#include <string>
#include <assimp/Importer.hpp>

#include "types.h"

#define SHADERS_FOLDER_DEFAULT_PATH     "../../shaders/"

class Reader
{
private:
    std::string shadersFolderPath = SHADERS_FOLDER_DEFAULT_PATH; 
    std::string modelsFolderPath  = SHADERS_FOLDER_DEFAULT_PATH;
    std::shared_ptr<Assimp::Importer> import = std::make_shared<Assimp::Importer>();
public:
    Reader() {}
    ~Reader() noexcept {}
    std::string readShader(const std::string& folderPath, const std::string& fileName);
    std::string readShader(const std::string& fileName);
    modelDataType readModelObj(const std::string& folderPath, const std::string& fileName);
    modelDataType readModelObj(const std::string& fileName);
};
using readerPtr = std::shared_ptr<Reader>;

#endif