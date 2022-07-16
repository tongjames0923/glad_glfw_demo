#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;


void main()
{
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

uniform vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}