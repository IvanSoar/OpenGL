#version 330 core
out vec4 fragmentColor;

in vec2 outTextureCoords;

uniform sampler2D u_Texture;
uniform vec3 textColor;

uniform float width;
uniform float edge;

void main()
{
	float distance = 1.0 - texture(u_Texture, outTextureCoords).a;
	float alpha = 1.0 - smoothstep(width, width + edge, distance);
	fragmentColor = vec4(textColor, alpha);
}