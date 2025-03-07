#ifndef CANVAS_H_

#define CANVAS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "types.h"


class Canvas
{
private:
    const GLuint width = 400;
    const GLuint height = 400;
    GLFWwindow* window = nullptr;
    const char* title = "Window";
    colorType bgColor = {1.0, 1.0, 1.0, 1.0};

public:
    Canvas(GLuint width, GLuint height, const char* title);
    ~Canvas();
    void setBackgroundColor(colorCompType r, colorCompType g, colorCompType b, colorCompType alpha);
    void setBackgroundColor(colorType& color);
    colorType getBackgroundColor() { return bgColor; }
    GLFWwindow* getWindow() { return window; }
};
using canvasPtr = std::shared_ptr<Canvas>;

#endif