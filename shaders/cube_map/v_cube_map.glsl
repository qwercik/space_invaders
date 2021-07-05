#version 330 core
layout (location = 0) in vec3 vertex;

out vec3 TexCoords;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    TexCoords = vertex;
    gl_Position = M * P * V * vec4(vertex, 1.0);
}

