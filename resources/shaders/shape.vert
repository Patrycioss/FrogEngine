#version 330 core
layout (location = 0) in vec2 vertex;// <vec2 position

void main()
{
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
}