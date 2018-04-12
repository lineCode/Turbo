#version 330

uniform int windowW;
uniform int windowH;

layout(location = 0) in vec3 vertex_pos;

void main()
{
    gl_Position = vec4(vertex_pos.x, vertex_pos.y, 0.0, 200.0);
}