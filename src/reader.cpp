#include <iostream>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "reader.h"
#include "exeptions.h"

std::string Reader::readShader(const std::string& folderPath, const std::string& fileName)
{
    std::ifstream file(folderPath + fileName);
    if (!file.is_open())
    {
        throw FileOpenError("Error while open file " + folderPath + fileName);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    std::string fileText = buffer.str();

    file.close();

    return fileText;
}

std::string Reader::readShader(const std::string& fileName)
{
    return readShader(shadersFolderPath, fileName);
}

modelDataType Reader::readModelObj(const std::string& folderPath, const std::string& fileName)
{
    const aiScene *scene = import->ReadFile(folderPath + fileName, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        throw ModelReadError("assimp error: " + std::string(import->GetErrorString()));
    }

    return scene;
}

modelDataType Reader::readModelObj(const std::string& fileName)
{
    return readModelObj(modelsFolderPath, fileName);
}
