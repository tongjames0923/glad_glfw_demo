#include "GL_Drawer.h"
struct ShaderSourceData
{
    string vertex;
    string fragment;
};
enum ShaderType
{
    None = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

static ShaderSourceData readShader(const string &shaderFile);
static unsigned int createShader(const string &vertex, const string &fragment);
static unsigned int makeShader(unsigned int type, const string &str);
bool isInit = false;
static void initOpenGL()
{
    if (!isInit)
    {
        if (!glfwInit())
            throw std::runtime_error("glfw fail");
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
        isInit = true;
    }
}

GLWindow::GLWindow()
{
    if (!isInit)
    {
        initOpenGL();
    }
}
int GLWindow::setWindowSizeCallBack(windowSizeCallback callback)
{
    if (window != nullptr)
    {
        glfwSetFramebufferSizeCallback(window, callback);
        return 1;
    }
    return 0;
}
void GLWindow::createWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
{
    //创建一个窗口对象
    window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("构造窗口失败");
    }
    //通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("glad 启动失败");
    }
}
void GLWindow::draw(drawCallback callback)
{

    if (window != nullptr)
    {
        int code = DRAW_CONTINUTE;
        while (!glfwWindowShouldClose(window) && code != DRAW_EXIT)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            code = callback(window); // 检查并调用事件，交换缓冲
            glfwSwapBuffers(window); //检查触发事件
            glfwPollEvents();        //交换颜色缓冲
        }
        glfwTerminate();
    }
}
Shader::Shader(const string &filepath)
{
    input(filepath);
}
Shader::Shader()
{
}
unsigned int Shader::getVAO()
{
    return VAO;
}
unsigned int Shader::getVBO()
{
    return VBO;
}
unsigned int Shader::getId()
{
    return id;
}
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::GenVertexBuffer(float *data, int len, int bufferType, int usage)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // GL_ARRAY_BUFFER	Vertex attributes
    // GL_ATOMIC_COUNTER_BUFFER	Atomic counter storage
    // GL_COPY_READ_BUFFER	Buffer copy source
    // GL_COPY_WRITE_BUFFER	Buffer copy destination
    // GL_DISPATCH_INDIRECT_BUFFER	Indirect compute dispatch commands
    // GL_DRAW_INDIRECT_BUFFER	Indirect command arguments
    // GL_ELEMENT_ARRAY_BUFFER	Vertex array indices
    // GL_PIXEL_PACK_BUFFER	Pixel read target
    // GL_PIXEL_UNPACK_BUFFER	Texture data source
    // GL_QUERY_BUFFER	Query result buffer
    // GL_SHADER_STORAGE_BUFFER	Read-write storage for shaders
    // GL_TEXTURE_BUFFER	Texture data buffer
    // GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
    // GL_UNIFORM_BUFFER	Uniform block storage
    glBindBuffer(bufferType, VBO);

    // GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY

    glBufferData(bufferType, len * sizeof(float), data, usage);
}
void Shader::enableVertexBuffer(int per, int stride, int index, int offset)
{
    glVertexAttribPointer(index, per, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void Shader::input(const string &filepath)
{
    ShaderSourceData source = readShader(filepath);
    id = createShader(source.vertex, source.fragment);
    hasShader = true;
}
void Shader::useShader()
{
    glUseProgram(id);
}
static unsigned int makeShader(unsigned int type, const string &str)
{
    //生成着色器
    unsigned int shader = glCreateShader(type);
    const char *src = str.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char *message = new char[len];
        glGetShaderInfoLog(shader, len, &len, message);
        cout << message << endl;
        delete[] message;
    }
    return shader;
}
static unsigned int createShader(const string &vertex, const string &fragment)
{

    unsigned int program = glCreateProgram();                         //产生着色器程序
    unsigned int vershader = makeShader(GL_VERTEX_SHADER, vertex);    //产生顶点着色器
    unsigned int fgshader = makeShader(GL_FRAGMENT_SHADER, fragment); //产生片段着色器
    glAttachShader(program, vershader);                               //将着色器加入着色器程序
    glAttachShader(program, fgshader);
    int success;
    char infoLog[512];
    glLinkProgram(program); //链接着色器
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
             << infoLog << std::endl;
    }
    // glValidateProgram(program);
    glDeleteShader(vershader); //删除源码对象
    glDeleteShader(fgshader);
    // id=program;
    return program;
}
static ShaderSourceData readShader(const string &shaderFile)
{
    ifstream s(shaderFile);
    string src;
    stringstream r[2];
    int type = ShaderType::None;
    while (getline(s, src))
    {
        if (src.find("#shader") != string::npos)
        {
            if (src.find("vertex") != string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (src.find("fragment") != string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::None)
            {
                r[type] << src << '\n';
            }
        }
    }
    return {r[ShaderType::VERTEX].str(), r[ShaderType::FRAGMENT].str()};
}