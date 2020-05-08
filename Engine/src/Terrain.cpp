#include "glad/glad.h"

#include <iostream>
#include <ctime>

#include "Terrain.h"
#include "Shaders.h"
#include "../ivsEngine.h"

Terrain& Terrain::get()
{
	static Terrain instance;
	return instance;
}

void Terrain::generate()
{
	srand(time(0));
	int tam = config::maxVertexperTerrain;
	get().verticesCount = tam * tam;
	float* vertices = new float[get().verticesCount * 3];

	int pointer = 0;
	for (int x = 0; x < tam; x++) {
		for (int y = 0; y < tam; y++) {
			vertices[pointer * 3 + 0] = (float)y / (tam - 1) * config::terrainSize;
			vertices[pointer * 3 + 1] = (float)(rand() % 2) - 0.5;
			vertices[pointer * 3 + 2] = (float)x / (tam - 1) * config::terrainSize;
			pointer++;
		}
	}

	tam--;
	get().indicesCount = tam * tam * 6;
	unsigned int* indices = new unsigned int[get().indicesCount];

	pointer = 0;
	for (int x = 0; x < tam; x++) {
		for (int y = 0; y < tam; y++) {
			int topLeft = (x * config::maxVertexperTerrain) + y;
			int topRight = topLeft + 1;
			int bottomLeft = ((x + 1) * config::maxVertexperTerrain) + y;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	glGenVertexArrays(1, &get().VAO);
	glBindVertexArray(get().VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, get().verticesCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, get().indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	get().x = -config::terrainSize / 2;
	get().z = -config::terrainSize / 2;
}

unsigned int Terrain::getVAO()
{
	return get().VAO;
}

unsigned int Terrain::getIndicesCount()
{
	return get().indicesCount;
}

int Terrain::getX()
{
	return get().x;
}

int Terrain::getZ()
{
	return get().z;
}

void Terrain::changeColor(float r, float g, float b, float a)
{
	Shaders::setUniform4f(glGetUniformLocation(Shaders::getShaders()[2], "color"), {r, g, b, a});
}
