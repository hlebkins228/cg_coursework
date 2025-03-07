#ifndef SHADER_H_

#define SHADER_H_

#include <GL/glew.h>
#include <string>
#include <memory>

#include "types.h"

#define FRAG_SHADER_DEFAULT_PATH        "..\\..\\shaders\\fragTest.shader"
#define VERTEX_SHADER_DEFAULT_PATH      "..\\..\\shaders\\vertexTest.shader"


enum stage
{
    compilation = 1,
    linking = 2
};

class Shaders
{
private:
    const GLchar* vertexShaderSource = nullptr;         
    const GLchar* fragmentShaderSource = nullptr;
    indexType shaderProgram = 0;

protected:
    void checkCompileErrors(indexType shader, enum stage type);
    
public:
    Shaders() {}
    ~Shaders() noexcept {}

    void setVertexShader(const GLchar* sourceCode);
    void setFragmentShader(const GLchar* sourceCode);
    void compileShaderProgram();
    
    indexType createShaderProgram();
    indexType getShaderProgram() { return shaderProgram; }
};
using shadersPtr = std::shared_ptr<Shaders>;

#endif