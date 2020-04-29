#pragma once

#include "vector"

class Terrain {
private:
	unsigned int VAO;
	unsigned int indicesCount;
	unsigned int verticesCount;
	int x, z;

private:
	Terrain() {}

public:
	static Terrain& get();
	static void generate();
	static unsigned int getVAO();
	static unsigned int getIndicesCount();
	static int getX();
	static int getZ();
	static void changeColor(float r, float g, float b, float a);
};