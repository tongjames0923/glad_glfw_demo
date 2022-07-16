#ifndef GL_DRAWER_H
#define GL_DRAWER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class GLWindow
{
private:
    GLFWwindow *window = nullptr;

public:
    GLWindow();
    static const int DRAW_EXIT = 0, DRAW_CONTINUTE = 1;
    using windowSizeCallback = void (*)(GLFWwindow *window, int width, int height);
    using drawCallback = int (*)(GLFWwindow *);
    int setWindowSizeCallBack(windowSizeCallback callback);
    void createWindow(int width, int height, const char *title, GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);
    void draw(drawCallback callback);
};
static void enableHighVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
}
class Shader
{
private:
    unsigned int id, VAO, VBO;
    bool hasShader = false;

public:
    Shader(const string &filepath);
    Shader();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getId();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void GenVertexBuffer(float *data, int len, int bufferType, int usage = GL_STATIC_DRAW);
    void enableVertexBuffer(int per, int stride, int index = 0, int offset = 0);
    void input(const string &filepath);
    void useShader();
};

#endif // !GL_DRAWER_H
