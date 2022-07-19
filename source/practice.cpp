#include "practice.h"
string shader_path = "../shaders/rect.frag";
int rect(GLFWwindow *w)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return GLWindow::DRAW_CONTINUTE;
}
void drawRect(GLWindow *window, float w, float h, float x, float y, float r, float g, float b)
{
    Shader s(shader_path);
    float ver[] = {
        x,
        y,
        r,
        g,
        b,
        x + w,
        y,
        r,
        g,
        b,
        x,
        y + h,
        r,
        g,
        b,
        x + w,
        y + h,
        r,
        g,
        b,
    };
    unsigned int indexs[]{
        0, 1, 2,
        1, 2, 3};
    s.GenVertexArray();
    s.makeBufferAndBind("VER", ver, sizeof(float), 20, GL_ARRAY_BUFFER);
    s.makeBufferAndBind("IND", indexs, sizeof(unsigned int), 6, GL_ELEMENT_ARRAY_BUFFER);
    s.enableVertexBuffer(2, 5, 0, 0);
    s.enableVertexBuffer(3, 5, 1, 2);
    window->useShader(s);
    window->draw(rect);
}