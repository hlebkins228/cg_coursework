#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shaders.h"
#include "exeptions.h"


void Shaders::setVertexShader(const GLchar* sourceCode)
{
    if (sourceCode == nullptr)
    {
        throw InvalidArgs("null vertex shader source code ptr!");
    }

    vertexShaderSource = sourceCode;
}

void Shaders::setFragmentShader(const GLchar* sourceCode)
{
    if (sourceCode == nullptr)
    {
        throw InvalidArgs("null fragment shader source code ptr!");
    }

    fragmentShaderSource = sourceCode;
}

void Shaders::compileShaderProgram()
{
    if (vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
    {
        throw NoShaderSource();
    }

    indexType vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, compilation);

    indexType fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, compilation);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, linking);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shaders::checkCompileErrors(indexType shader, enum stage type)
{
    int success;
    char infoLog[1024];

    if (type == compilation)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        else
        {
            std::cerr << "Shader compilation complete!" << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        else
        {
            std::cerr << "Shader program linking complete!" << std::endl;
        }
    }
}

indexType Shaders::createShaderProgram()
{
    compileShaderProgram();
    return shaderProgram;
}