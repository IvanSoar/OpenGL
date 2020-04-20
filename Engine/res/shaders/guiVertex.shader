#version 330 core
layout (location = 0) in vec2 aPos;

out vec3 ourColor;
out vec3 ourPos;

uniform mat4 model;
uniform mat4 projection;
uniform vec3 color;

void main()
{
    gl_Position = projection * model * vec4(aPos, 0.0f, 1.0f);
    ourColor = color;
}