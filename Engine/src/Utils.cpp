#include "Utils.h"

#include <string>
#include <iostream>

void nk::Log(const std::string& msg, int type)
{
	switch (type) {
	case 0: std::cout << NIKKO_LOG_STAMP << msg << NIKKO_FAILURE << std::endl; break;
	case 1: std::cout << NIKKO_LOG_STAMP << msg << NIKKO_SUCCESS << std::endl; break;
	case 2: std::cout << NIKKO_LOG_STAMP << msg << std::endl; break;
	}
}

int calcStride(int x, int y, int size) {
	return y * size + x;
};

//nk::grid* nk::generateTerrain(int quads) {
//	quads++;
//	int size = (quads) * (quads) * 3;
//	float* terrainArray = new float[size];
//
//	for (int x = 0; x < quads; x++) {
//		for (int y = 0; y < quads; y++) {
//			int stride = calcStride(x, y, quads) * 3;
//			terrainArray[stride + 1] = y * 1.f;
//			terrainArray[stride + 2] = 0.0f;
//		}
//	}
//
//	quads--;
//	size = quads * quads * 6;
//	int* terrainIndex = new int[size];
//
//	for (int x = 0; x < quads; x++) {
//		for (int y = 0; y < quads; y++) {
//			terrainIndex[calcStride(x, y, quads) + 0] = calcStride(x + 0, y + 0, quads + 1);
//			terrainIndex[calcStride(x, y, quads) + 1] = calcStride(x + 0, y + 1, quads + 1);
//			terrainIndex[calcStride(x, y, quads) + 2] = calcStride(x + 1, y + 1, quads + 1);
//
//			terrainIndex[calcStride(x, y, quads) + 3] = calcStride(x + 1, y + 1, quads + 1);
//			terrainIndex[calcStride(x, y, quads) + 4] = calcStride(x + 1, y + 0, quads + 1);
//			terrainIndex[calcStride(x, y, quads) + 5] = calcStride(x + 0, y + 0, quads + 1);
//		}
//	}
//
//	return terrainArray;
//}