#include <GL/glew.h>
#include <iostream>

#include "render.h"
#include "exeptions.h"


Render::Render(canvasPtr canvas, shadersPtr shaders, cameraPtr camera) : canvas(canvas), shaders(shaders), camera(camera)
{

}

Render::~Render()
{

}

void Render::setupModel(polygonModelPtr model)
{
    idType currentModelId; 
    glGenBuffers(1, &currentModelId.VBO);
    glGenBuffers(1, &currentModelId.EBO);
    glGenVertexArrays(1, &currentModelId.VAO);
    
    glBindVertexArray(currentModelId.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, currentModelId.VBO);
    glBufferData(GL_ARRAY_BUFFER, DEFAULT_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentModelId.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, DEFAULT_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    models.push_back(model);       // сохраняем ссылку на модель и связанные с ней идентификаторы буферов
    model->setRenderParams(currentModelId.VAO, shaders->getShaderProgram());
}

void Render::render()
{
    colorType bgColor = canvas->getBackgroundColor();
    GLFWwindow* window = canvas->getWindow();
    indexType shaderProgram = shaders->getShaderProgram();
    GLint width, height, uniformWindowSize;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glfwGetFramebufferSize(window, &width, &height);
    uniformWindowSize = glGetUniformLocation(shaderProgram, "windowSize");
    glUseProgram(shaderProgram);
    glUniform2f(uniformWindowSize, static_cast<float>(width), static_cast<float>(height));


    float cameraAngleX = 1.0, cameraAngleY = 0.8, cameraAngleZ = 0.0;
    float rotateSpeed = 0.03;
    bool cameraChanged = true;

    models[0]->scale(0.5, 0.5, 0.5);
    models[0]->rotate(-1.5, 0.5, 0.0);
    models[0]->move(0.0, 0.0, 0.0);

    mat4Type viewMatrix = mat4Type(1.0);

    models[0]->updateViewMatrix(viewMatrix);
    models[0]->draw();
    mat4Type trans = models[0]->getTransformMatrix();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << trans[i][j] << " ";
        }
        std::cout << std::endl;
    }

    models[0]->printVertices();
    std::cout << "-------------------\n";
    models[0]->transformVertices();
    models[0]->draw();
    models[0]->printVertices();

    cameraChanged = false; // temp

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        // {
        //     cameraAngleY -= rotateSpeed;
        //     cameraChanged = true;
        // }
        // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        // {
        //     cameraAngleY += rotateSpeed;
        //     cameraChanged = true;
        // }
        // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        // {
        //     cameraAngleX += rotateSpeed;
        //     cameraChanged = true;
        // }
        // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        // {
        //     cameraAngleX -= rotateSpeed;
        //     cameraChanged = true;
        // }

        if (cameraChanged)
        {
            camera->rotate(cameraAngleX, cameraAngleY, cameraAngleZ);
            viewMatrix = camera->getViewMatrix();
        }

        for (const polygonModelPtr model: models)
        {                            
            if (cameraChanged)
            {
                model->updateViewMatrix(viewMatrix);
            }
            model->draw();
        }
        cameraChanged = false;

        glfwSwapBuffers(window);
    }

}