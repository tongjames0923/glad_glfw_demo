
#include "GL_Drawer.h"
// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;
Shader s;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int program;
int draw(GLFWwindow *window)
{
    s.useShader();
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(program, "ourColor");
    glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return GLWindow::DRAW_CONTINUTE;
}
int main(int argc, char *argv[])
{
    GLWindow window;
    // glfwSetErrorCallback(glfw_error_callback);
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f,   // top
    };
    s.input("../shaders/baseShader.frag");
    program = s.getId();
    s.GenVertexBuffer(vertices, 3 * 3, GL_ARRAY_BUFFER);
    s.enableVertexBuffer(3, 3);
    window.draw(draw);
    return EXIT_SUCCESS;
}
