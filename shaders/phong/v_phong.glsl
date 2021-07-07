#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 sun;
uniform vec3 moon;

layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texCoord;

out vec4 l1;
out vec4 l2;
out vec4 n;
out vec4 v;
out vec4 r1;
out vec4 r2;
out vec2 iTexCoord;

void main(void)
{
    gl_Position = P * V * M * vertex;
    
    l1 = normalize(V * vec4(moon, 1) - V * M * vertex);
    l2 = normalize(V * vec4(sun, 1) - V * M * vertex);

    n = normalize(V * M * normal);
    r1 = normalize(reflect(-l1, n));
    r2 = normalize(reflect(-l2, n));

    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex);

    iTexCoord = texCoord;
}
