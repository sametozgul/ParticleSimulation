#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in mat4 instanceMatrix;
out vec3 color;

// uniform mat4 model;

void main(void)
{
    gl_Position = instanceMatrix * vec4(aPos, 1.0);
    color = aColor;
}
