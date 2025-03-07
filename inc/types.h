#ifndef TYPES_H_

#define TYPES_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <assimp/scene.h>

using cordType          = GLfloat;
using colorCompType     = GLfloat;
using indexType         = GLuint;
using edgeType          = indexType;
using sizeType          = GLsizei;
using shaderSrcType     = const GLchar*;
using modelDataType     = const aiScene*;
using mat3Type          = glm::mat3x3;
using mat4Type          = glm::mat4x4;
using vec3Type          = glm::vec3;
using vec4Type          = glm::vec4;


#pragma pack(push, 1)
struct coords
{
    cordType x;
    cordType y;
    cordType z;
};
#pragma pack(pop)
using coordsType = struct coords;

#pragma pack(push, 1)
struct color
{
    colorCompType r;
    colorCompType g;
    colorCompType b;
    colorCompType a;
};
#pragma pack(pop)
using colorType = struct color;

// индексы вершин в массиве вершин
struct edges
{
    edgeType v1;
    edgeType v2;
    edgeType v3;
};
using edgesType = struct edges;

struct normal
{
    cordType x;
    cordType y;
    cordType z;
};
using normalType = struct normal;

struct id
{
    indexType VAO;
    indexType VBO;
    indexType EBO;
};
using idType = struct id;


#endif
