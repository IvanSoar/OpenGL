#version 330 core
out vec4 FragColor;

in vec2 outTextureCoord;

uniform sampler2D u_Texture;
uniform vec4 color;

void main()
{
	vec4 texColor = texture(u_Texture, outTextureCoord);
	FragColor = color;
}