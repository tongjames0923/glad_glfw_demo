#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1)in vec3 color;
out vec3 dcolor;
void main()
{
	gl_Position = vec4(aPos,0, 1.0);
    dcolor=color;
}
#shader fragment
#version 330 core
in vec3 dcolor;
out vec4 FragColor;
uniform vec3 mycolor;
void main()
{
	FragColor = vec4(mycolor,0);
	//mycolor=dcolor;
}