#version 330 core
out vec4 fragColor;

in vec4 outColor;
in vec3 outPos;

void main()
{
	fragColor = vec4(outColor.r, outColor.g * outPos.y , outColor.b, outColor.a);
}