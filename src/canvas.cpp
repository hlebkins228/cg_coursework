#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "canvas.h"
#include "exeptions.h"
#include "types.h"


Canvas::Canvas(GLuint width, GLuint height, const char* title) : width(width), height(height), title(title)
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        throw WindowCreateError();
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
}

Canvas::~Canvas()
{
    glfwTerminate();
}

void Canvas::setBackgroundColor(colorCompType r, colorCompType g, colorCompType b, colorCompType alpha)
{
    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1 || alpha < 0 || alpha > 1)
    {
        throw InvalidArgs("Invalid color values");
    } 

    bgColor = {r, g, b, alpha};
}

void Canvas::setBackgroundColor(colorType& color)
{
    bgColor = color;
}
