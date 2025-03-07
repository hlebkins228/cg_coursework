#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <iostream>
#include <assert.h>

#include "polygon_model.h"
#include "types.h"
#include "exeptions.h"


void Face::writeDataToArray(edgeType* array, indexType& index)
{
    if (array == nullptr)
    {
        throw InvalidArgs("null edges array ptr");
    }

    array[index + 0] = edges.v1;
    array[index + 1] = edges.v2;
    array[index + 2] = edges.v3;

    index += 3;
}


void Vertex::writeDataToArray(cordType* array, indexType& index)
{
    if (array == nullptr)
    {
        throw InvalidArgs("null coords array ptr");
    }

    // coords
    array[index + 0] = coords.x;
    array[index + 1] = coords.y;
    array[index + 2] = coords.z;
    // color
    array[index + 3] = color.r;
    array[index + 4] = color.g;
    array[index + 5] = color.b;
    array[index + 6] = color.a;

    index += 7;
}

void Vertex::transform(mat4Type& matrix)
{
    vec4Type coordsVec = vec4Type(coords.x, coords.y, coords.z, 1.0);
    vec4Type transformedCoordsVec = coordsVec * matrix;
    coords.x = transformedCoordsVec.x;
    coords.y = transformedCoordsVec.y;
    coords.z = transformedCoordsVec.z;
}

// BaseModel
PolygonModel::PolygonModel()
{
    verticesArray = new cordType[VERTICES_ARRAY_DEFAULT_SIZE];
    if (verticesArray == nullptr)
    {
        throw MemoryAllocError();
    }
    verticesArraySize = 0;

    facesArray = new indexType[EDGES_ARRAY_DEFAULT_SIZE];
    if (facesArray == nullptr)
    {
        throw MemoryAllocError();
    }
    facesArraySize = 0;

    verticesVector = std::make_shared<vertexVec>();
    facesVector = std::make_shared<faceVec>();
}

PolygonModel::~PolygonModel()
{ 
    delete[] verticesArray;
    delete[] facesArray;
}

void PolygonModel::addVertex(Vertex& v)
{
    verticesVector->push_back(std::make_shared<Vertex>(v));
}
void PolygonModel::addVertex(vertexPtr v)
{
    verticesVector->push_back(v);  
}
void PolygonModel::addVertex(coordsType& coords, colorType& color, normalType& normal)
{
    verticesVector->push_back(std::make_shared<Vertex>(coords, color, normal));
}
void PolygonModel::addFace(edgesType& edges)
{
    facesVector->push_back(std::make_shared<Face>(edges));
}

void PolygonModel::addPolygon(Vertex& v1, Vertex& v2, Vertex& v3, normalType& normal)
{
    // vertex
    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
    // face    
    edgesType edges = { verticesCount + 0, verticesCount + 1, verticesCount + 2 }; 
    addFace(edges);
    verticesCount += 3;
}

void PolygonModel::updateFacesArray()
{
    if (facesArray == nullptr)
    {
        throw InvalidArgs("null faces array ptr");
    }

    indexType index = 0;
    for (const facePtr face: *facesVector)
    {
        face->writeDataToArray(facesArray, index);
    }
    facesArraySize = index;
    facesChanged = false;
}

void PolygonModel::updateVerticesArray()
{
    if (verticesArray == nullptr)
    {
        throw InvalidArgs("null vertices array ptr");
    }

    indexType index = 0;
    for (const vertexPtr vertex: *verticesVector)
    {
        vertex->writeDataToArray(verticesArray, index);
    }
    verticesArraySize = index;
    verticesChanged = false;
}

void PolygonModel::activate()
{
    if (verticesVector == nullptr || verticesVector->size() == 0)
    {
        throw ModelNotReady("vertices null array or zero size");
    }
    else if (facesVector == nullptr || facesVector->size() == 0)
    {
        throw ModelNotReady("faces null array or zero size");
    }
    else if (VAO == 0)
    {
        throw ModelNotReady("VAO buffer id does not set");    
    }
    else if (shaderProgram == 0)
    {
        throw ModelNotReady("shader program id does not set");    
    }
    else
    {
        modelReady = true;
    }
}

void PolygonModel::deactivate()
{
    modelReady = false;
}

void PolygonModel::draw()
{   
    if (!modelReady)
    {
        return;
    }
    
    glBindVertexArray(VAO);

    if (verticesChanged)
    {
        std::cout << "bebebebebeb\n";
        updateVerticesArray();
        glBufferSubData(GL_ARRAY_BUFFER, 0, verticesArraySize * sizeof(cordType), verticesArray);
    }
    if (facesChanged)
    {
        updateFacesArray();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, facesArraySize * sizeof(indexType), facesArray);
    }
    
    if (worldMatrixChanged)
    {
        updateWorldMatrix();
    }
    if (projectionMatrixChanged)
    {
        updateProjectionMatrix();
    }
    if (transformMatrixChanged)
    {
        std::cout << "hahahahha\n";
        updateTransformMatrix();
        GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    }

    glDrawElements(GL_TRIANGLES, facesArraySize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void PolygonModel::readModelFromScene(modelDataType scene)
{
    processNode(scene->mRootNode, scene);
}

void PolygonModel::processNode(aiNode *node, modelDataType scene)
{
    if (node == nullptr)
    {
        return;
    }
    aiMesh* mesh;

    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        mesh = scene->mMeshes[node->mMeshes[i]]; 
        proccessMeshVertices(mesh);
        proccessMeshFaces(mesh);
    }
    if (node->mNumChildren == 0)
    {
        return;
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void PolygonModel::proccessMeshVertices(aiMesh* mesh)
{
    if (mesh == nullptr)
    {
        return;
    }

    aiVector3D* vertices = mesh->mVertices;
    aiVector3D* normalsArray = mesh->mNormals;
    aiColor4D** colorsArray = mesh->mColors;
    coordsType vertexCoords;
    colorType color = {1.0, 0.0, 0.0, 1.0};
    normalType normal = {1.0, 1.0, 1.0};
    for (indexType i = 0; i < mesh->mNumVertices; ++i)
    {
        vertexCoords = {vertices[i].x, vertices[i].y, vertices[i].z};
        if (normalsArray != nullptr)
        {
            normal = {normalsArray[i].x,normalsArray[i].y, normalsArray[i].z};
        }
        // if (colorsArray != nullptr && colorsArray[i] != nullptr)
        // {
        //     color = {colorsArray[i][0].r, colorsArray[i][0].g, colorsArray[i][0].b, 1.0};   
        // }
        addVertex(vertexCoords, color, normal);
    }
}

void PolygonModel::proccessMeshFaces(aiMesh* mesh)
{
    if (mesh == nullptr)
    {
        return;
    }
    
    aiFace* facesArray = mesh->mFaces;
    indexType* indices;
    edgesType face;

    for (indexType i = 0; i < mesh->mNumFaces; ++i)
    {
        indices = facesArray[i].mIndices;
        face = {indices[0], indices[1], indices[2]};        // считаем что всегда 3, так ка считывали с опцией triangulate
        addFace(face);
    }
}

void PolygonModel::scale(cordType kx, cordType ky, cordType kz)
{
    scaleVec.x = kx;
    scaleVec.y = ky;
    scaleVec.z = kz;
    worldMatrixChanged = true;
}
void PolygonModel::move(cordType dx, cordType dy, cordType dz)
{
    moveVec.x = dx;
    moveVec.y = dy;
    moveVec.z = dz;
    worldMatrixChanged = true;
}

void PolygonModel::rotate(float angleX, float angleY, float angleZ)
{
    rotateVec.x = angleX;
    rotateVec.y = angleY;
    rotateVec.z = angleZ;
    worldMatrixChanged = true;
}

void PolygonModel::updateWorldMatrix()
{
    mat4Type mScale = mat4Type(0.0);
    mScale[0][0] = scaleVec.x;
    mScale[1][1] = scaleVec.y;
    mScale[2][2] = scaleVec.z;
    mScale[3][3] = 1.0;

    mat4Type mMove = mat4Type(
        vec4Type(1.0, 0.0, 0.0, 0.0),
        vec4Type(0.0, 1.0, 0.0, 0.0),
        vec4Type(0.0, 0.0, 1.0, 0.0),
        vec4Type(moveVec.x, moveVec.y, moveVec.z, 1.0)
    );

    mat4Type mRotate = getRotationMatrix(rotateVec);

    worldMatrix = mMove * mRotate * mScale;
    worldMatrixChanged = false;
    transformMatrixChanged = true;
}

void PolygonModel::updateViewMatrix(mat4Type& viewMatrix)
{
    this->viewMatrix = viewMatrix;

    transformMatrixChanged = true;
}

void PolygonModel::updateProjectionMatrix()
{
    projectionMatrixChanged = false;
    transformMatrixChanged = true;
}

void PolygonModel::updateTransformMatrix()
{
    transformMatrix = projectionMatrix * viewMatrix * worldMatrix;

    transformMatrixChanged = false;
}

void PolygonModel::printVertices()
{
    float maxVal = -10.0;
    float minVal = 10.0;
    
    for (int i = 0; i < verticesArraySize; ++i) {
        if (verticesArray[i] > maxVal) {
            maxVal = verticesArray[i];
        }
        else if (verticesArray[i] < minVal) {
            minVal = verticesArray[i];
        }
    }

    std::cout << "min: " << minVal << " max: " << maxVal << std::endl;
}


void PolygonModel::transformVertices()
{
    for (auto& elem: *verticesVector)
    {
        elem->transform(transformMatrix);
    }
    verticesChanged = true;
}