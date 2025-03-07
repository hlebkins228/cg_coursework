#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <exception>
#include <iostream>

#include "polygon_model.h"
#include "camera.h"
#include "render.h"
#include "types.h"
#include "reader.h"
#include "exeptions.h"


int main(void)
{
    try
    {
        canvasPtr canvas = std::make_shared<Canvas>(1800, 1800, "test");
        readerPtr reader = std::make_shared<Reader>();
        shadersPtr shaders = std::make_shared<Shaders>();
        cameraPtr camera = std::make_shared<Camera>();
        polygonModelPtr model1 = std::make_shared<PolygonModel>();

        canvas->setBackgroundColor(1.0, 1.0, 1.0, 1.0);
        std::string vertexShaderSrc = reader->readShader("vertex.shader");
        std::string fragmentShaderSrc = reader->readShader("frag.shader");
        shaders->setVertexShader(vertexShaderSrc.c_str());
        shaders->setFragmentShader(fragmentShaderSrc.c_str());
        shaders->createShaderProgram();

        Render render(canvas, shaders, camera);

        model1->readModelFromScene(reader->readModelObj("monkey.obj"));
        render.setupModel(model1);
        
        render.render();
    }
    catch (BaseError e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
