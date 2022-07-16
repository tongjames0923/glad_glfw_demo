
#include "GL_Drawer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void error_callback(int code, const char *description)
{

    cout << description << endl;
}

int glDraw(GLFWwindow *w)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex2f(0.0f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0, 1, 0);
    glEnd();
    return GLWindow::DRAW_CONTINUTE;
}

void red_triangle()
{
    GLWindow window;
    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    s.input("../shaders/red_trangle.frag");
    float data[] = {
        -0.5, -0.5,
        0, 0.5,
        0.5, -0.5};
    s.GenVertexBuffer(data, 6, GL_ARRAY_BUFFER);
    s.enableVertexBuffer(2, 2);
    s.useShader();
    window.draw(draw);
}
int better(GLFWwindow *w)
{
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    glUniform3f(glGetUniformLocation(s.getId(), "myColor"), 0, greenValue, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return GLWindow::DRAW_CONTINUTE;
}
void better_triangle()
{
    GLWindow window;
    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    s.input("../shaders/better_triangle.frag");
    float data[] = {
        -0.5, -0.5,
        0, 0.5,
        0.5, -0.5};
    s.GenVertexBuffer(data, 6, GL_ARRAY_BUFFER);
    s.enableVertexBuffer(2, 2);
    s.useShader();
    window.draw(better);
}
float offset[] = {
    0, 0};
int drawScale(GLFWwindow *w)
{
    float timeValue = glfwGetTime();
    float vers[][3] = {
        {0.5, 0, 0},
        {-0.5, 0, 0},
        {0, 0.5, 0}};

    float x = (sin(timeValue) / 2.0f) + 0.5f;
    if (glfwGetKey(w, GLFW_KEY_A))
    {
        offset[0] -= 0.01;
    }
    else if (glfwGetKey(w, GLFW_KEY_D))
    {
        offset[0] += 0.01;
    }
    else if (glfwGetKey(w, GLFW_KEY_W))
    {
        offset[1] += 0.01;
    }
    else if (glfwGetKey(w, GLFW_KEY_S))
    {
        offset[1] -= 0.01;
        cout << "key S" << endl;
        cout << offset[0] << endl
             << offset[1] << endl;
    }
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
    {
        glm::vec4 vec(vers[i][0], vers[i][1], vers[i][2], 0);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(1.2f * x, 1.2f * x, 1.2f * x));
        vec = trans * vec;
        glVertex3f(vec.x + offset[0], vec.y + offset[1], vec.z);
    }
    glEnd();
    return GLWindow::DRAW_CONTINUTE;
}
void scaling_triangle()
{
    GLWindow window;
    // enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    // s.input("../shaders/better_triangle.frag");
    // float data[] = {
    //     -0.5, -0.5,
    //     0, 0.5,
    //     0.5, -0.5};
    // s.GenVertexBuffer(data, 6, GL_ARRAY_BUFFER);
    // s.enableVertexBuffer(2, 2);
    // s.useShader();
    window.draw(drawScale);
}
int main(int argc, char *argv[])
{
    scaling_triangle();
    return EXIT_SUCCESS;
}
