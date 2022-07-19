
#include "GL_Drawer.h"
#include "practice.h"
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
GLWindow window;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int program;
int draw(GLFWwindow *w)
{
    window.useShader(s);
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

    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    s.input("../shaders/red_trangle.frag");
    float data[] = {
        -0.5, -0.5,
        0, 0.5,
        0.5, -0.5};
    s.GenVertexArray();
    s.makeBufferAndBind("VBO", data, sizeof(float), 6, GL_ARRAY_BUFFER);
    s.enableVertexBuffer(2, 2);
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
    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    s.input("../shaders/better_triangle.frag");
    float data[] = {
        -0.5, -0.5,
        0, 0.5,
        0.5, -0.5};
    s.GenVertexArray();
    s.makeBufferAndBind("VBO", data, sizeof(float), 6, GL_ARRAY_BUFFER);
    s.enableVertexBuffer(2, 2);
    window.useShader(s);
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
int drawTex(GLFWwindow *w)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return GLWindow::DRAW_CONTINUTE;
}
void texdemo()
{
    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    TextureItem item("/Users/abstergo/Downloads/wall.jpg");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, item.getWidth(), item.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, item.getData());
    glGenerateMipmap(GL_TEXTURE_2D);
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    s.input("../shaders/tex.frag");
    s.GenVertexArray();
    s.makeBufferAndBind("VBO", vertices, sizeof(float), 32, GL_ARRAY_BUFFER);
    s.makeBufferAndBind("EBO", indices, sizeof(unsigned int), 6, GL_ELEMENT_ARRAY_BUFFER);
    s.enableVertexBuffer(3, 8, 0, 0);
    s.enableVertexBuffer(3, 8, 1, 3);
    s.enableVertexBuffer(2, 8, 2, 6);

    window.useShader(s);
    window.draw(drawTex);
}
int main(int argc, char *argv[])
{
    enableHighVersion();
    window.createWindow(SCR_WIDTH, SCR_HEIGHT, "opengl");
    drawRect(&window, 1, 1, -0.5, -0.5, 1, 1, 0);
    return EXIT_SUCCESS;
}
