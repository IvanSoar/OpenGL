#version 330 core
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inTextureCoords;

out vec2 outTextureCoords;

void main()
{
    gl_Position = vec4(inPos, 0.0f, 1.0f);
    outTextureCoords = inTextureCoords;
}