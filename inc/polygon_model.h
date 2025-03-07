#ifndef POLYGON_MODEL_H_

#define POLYGON_MODEL_H_

#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <vector>
#include <memory>

#include "model.h"
#include "types.h"

#define VERTICES_ARRAY_DEFAULT_SIZE         40960
#define EDGES_ARRAY_DEFAULT_SIZE            20480


class Vertex
{
private:
    coordsType coords;
    colorType color;
    normalType normal;
    
public:
    Vertex(coordsType& coords, colorType& color, normalType& normal) : coords(coords), color(color), normal(normal) {}
    void transform(mat4Type& matrix);

    void writeDataToArray(cordType* array, indexType& index);
};
using vertexPtr = std::shared_ptr<Vertex>;
using vertexVec = std::vector<vertexPtr>;
using vertexVecPtr = std::shared_ptr<vertexVec>;


class Face
{
private:
    edgesType edges;
    
public:
    explicit Face(edgesType& edges) : edges(edges) {}
    void writeDataToArray(edgeType* array, indexType& index);
};
using facePtr = std::shared_ptr<Face>;
using faceVec = std::vector<facePtr>;
using faceVecPtr = std::shared_ptr<faceVec>;


class PolygonModel: BaseModel
{
protected:
    // vertices
    vertexVecPtr verticesVector = nullptr;
    cordType* verticesArray = nullptr;
    indexType verticesArraySize = 0;
    indexType verticesCount = 0;        // для того чтобы определять индекс добавленной вершины

    // Edges
    faceVecPtr facesVector = nullptr;
    indexType* facesArray = nullptr;
    indexType facesArraySize = 0;

    indexType VAO = 0;
    indexType shaderProgram = 0;
    
    bool modelReady = false;        // готова ли модель к отрисовке
    bool facesChanged = true;       // изменялись ли поверхности модели
    bool verticesChanged = true;       // изменялись ли вершины модели
    bool worldMatrixChanged = true;
    bool projectionMatrixChanged = true;
    bool transformMatrixChanged = true;

    // вектора преобразований
    vec3Type scaleVec = vec3Type(1.0, 1.0, 1.0);    // масштабирование по осям x, y, z
    vec3Type rotateVec = vec3Type(0.0, 0.0, 0.0);   // поворот вокруг осей x, y, z
    vec3Type moveVec = vec3Type(0.0, 0.0, 0.0);     // перемещение по осям x, y, z

    // матрицы преобразований
    mat4Type worldMatrix = mat4Type(1.0);
    mat4Type viewMatrix = mat4Type(1.0);
    mat4Type projectionMatrix = mat4Type(1.0);
    mat4Type transformMatrix = mat4Type(1.0);       // матрица полного преобразования координат

    void proccessMeshVertices(aiMesh* mesh);
    void proccessMeshFaces(aiMesh* mesh);
    void processNode(aiNode *node, modelDataType scene);

public:
    PolygonModel();
    ~PolygonModel() noexcept;

    void addVertex(Vertex& v);
    void addVertex(vertexPtr v);
    void addVertex(coordsType& coords, colorType& color, normalType& normal);
    void addFace(edgesType& edges);
    void addPolygon(Vertex& v1, Vertex& v2, Vertex& v3, normalType& normal);

    void updateFacesArray();
    void updateVerticesArray();

    void updateWorldMatrix();
    void updateViewMatrix(mat4Type& viewMatrix);
    void updateProjectionMatrix();
    void updateTransformMatrix();

    void readModelFromScene(modelDataType scene);
    
    void setRenderParams(indexType buffersId, indexType shadersId) { VAO = buffersId; shaderProgram = shadersId; modelReady = true; }
    void activate();    // проверяет готовность модели. Если готова, изменяет modelReady на true, иначе бросает исключение ModelNotReady
    void deactivate();  // изменяет modelReady на false

    // базовые преобразования
    void scale(cordType kx, cordType ky, cordType kz);
    void move(cordType dx, cordType dy, cordType dz);
    void rotate(float angleX, float angleY, float angleZ);

    virtual void draw() override;

    void transformVertices();
    void printVertices();
    mat4Type getTransformMatrix() { return transformMatrix; }
};
using polygonModelPtr = std::shared_ptr<PolygonModel>;

#endif
