
#include "GL_Drawer.h"
// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int draw(GLFWwindow *window)
{
    glDrawArrays(GL_TRIANGLES,0,3);
    return GLWindow::DRAW_CONTINUTE;
}
int main(int argc, char *argv[])
{
    GLWindow window;
    //glfwSetErrorCallback(glfw_error_callback);
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    float pos[] = {-0.5f, -0.5f,
                   0, 0.5f,
                   0.5f, -0.5f};
                   Shader s("../shaders/baseShader.frag");
                   s.GenVertexBuffer(pos,6,GL_ARRAY_BUFFER);
                   s.enableVertexBuffer(2);
                   s.useShader();
    window.draw(draw);
    return EXIT_SUCCESS;
}