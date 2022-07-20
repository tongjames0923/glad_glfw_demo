#ifndef GL_DRAWER_H
#define GL_DRAWER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

class GLWindow;
class Shader;
class TextureItem
{
private:
    unsigned char *data = nullptr;
    int w = -1, h = -1, chanel = -1;
    string file = "NULL";

public:
    ~TextureItem();
    TextureItem();
    TextureItem(const string &file);
    void readTex(const string &file);
    int getWidth() const;
    int getHeight() const;
    int getChanel() const;
    unsigned char *getData() const;
};
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
    void useShader(const Shader &sh);
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
    unsigned int id, VAO;
    map<string, unsigned int> objs;
    bool hasShader = false;

public:
    Shader(const string &filepath);
    Shader();
    bool hasGenedBuffer(const string &name);
    unsigned int getBufferIdByName(const string &name);
    unsigned int getVAO() const;
    unsigned int getId() const;
    Shader &makeBufferAndBind(string objName, void *data, int datasize, int len, int bufferType, int usage = GL_STATIC_DRAW);
    Shader &GenVertexArray();
    Shader &enableVertexBuffer(int per, int stride, int index = 0, int offset = 0);
    Shader &input(const string &filepath);
};

#endif // !GL_DRAWER_H
