#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 ourColor;
out vec3 ourPos;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 color;


void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0f);
    ourColor = color;
}