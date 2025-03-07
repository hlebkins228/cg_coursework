#ifndef RENDER_H_

#define RENDER_H_

#include <GLFW/glfw3.h>
#include <map>

#include "types.h"
#include "polygon_model.h"
#include "camera.h"
#include "shaders.h"
#include "canvas.h"

#define DEFAULT_BUFFER_SIZE     10240 * 3 * sizeof(float)


class Render
{
private:
    std::vector<polygonModelPtr> models;
    canvasPtr canvas = nullptr;
    shadersPtr shaders = nullptr;
    cameraPtr camera = nullptr;

public:
    Render(canvasPtr canvas, shadersPtr shaders, cameraPtr camera);
    ~Render();
    void setupModel(polygonModelPtr model);
    void render();
};

#endif