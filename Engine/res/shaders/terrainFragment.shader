#version 330 core
out vec4 fragColor;

in vec4 outColor;
in vec3 outPos;

void main()
{
	if(outPos.y < 0.0)
		fragColor = vec4(0.0, 0.0, 1.0, 1.0);
	else if (outPos.y < 0.2)
		fragColor = vec4(0.8, 0.8, 0.6, 1.0);
	else if (outPos.y < 0.6)
		fragColor = vec4(0.4, 0.8, 0.5, 1.0);
}