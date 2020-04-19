#include <glad/glad.h>

#include "ModelManager.h"
#include "Utils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

RawModel ModelManager::loadModel(const std::string& filename)
{
	float v1, v2, v3, v4, v5, v6;
	unsigned int i1, i2, i3;
	unsigned int vertex = 0;
	unsigned int index = 0;

	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;

	std::ifstream file(MODELS_DIR + filename + MODELS_EXT, std::ifstream::in);
	std::string line;

	while (!file.eof()) {
		getline(file, line);
		if (line.find("v") != std::string::npos) {
			std::stringstream stream;
			stream << line.substr(2, std::string::npos);
			stream >> v1 >> v2 >> v3 >> v4 >> v5 >> v6;
			vertexData.push_back(v1);
			vertexData.push_back(v2);
			vertexData.push_back(v3);
			vertexData.push_back(v4);
			vertexData.push_back(v5);
			vertexData.push_back(v6);
			vertex++;
		}
		else if (line.find("f") != std::string::npos) {
			std::stringstream stream;
			stream << line.substr(2, std::string::npos);
			stream >> i1 >> i2 >> i3;
			indexData.push_back(i1);
			indexData.push_back(i2);
			indexData.push_back(i3);
			index += 3;
		}
	}

	file.close();
	return { vertexData, indexData, vertex, index };
}



void ModelManager::add(const std::string& filename, model_t type)
{
	RawModel* rModel = new RawModel(loadModel(filename));

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, rModel->vertexCount * 6 * sizeof(float), rModel->vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rModel->indexCount * sizeof(unsigned int), rModel->indexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Model* model = new Model(generateModelId(), filename, type, VAO, rModel->vertexCount, rModel->indexCount);
	models.emplace(std::pair<unsigned int, Model*>(model->getID(), model));
}

Model& ModelManager::getModel(unsigned int modelId)
{
	return *models[modelId];
}

unsigned int ModelManager::getLast()
{
	return models.size();
}

unsigned int ModelManager::generateModelId()
{
	return models.size() + 1;
}



void Model::move(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Model::rotate(float dx, float dy, float dz)
{
	rotation.x += dx;
	rotation.y += dy;
	rotation.z += dz;
}

void Model::scale(float value)
{
	scaleFactor.x = value;
	scaleFactor.y = value;
	scaleFactor.z = value;
}

void Model::scale(float dx, float dy, float dz)
{
	scaleFactor.x = dx;
	scaleFactor.y = dy;
	scaleFactor.z = dz;
}

void Model::setPosition(float dx, float dy, float dz)
{
	position.x = dx;
	position.y = dy;
	position.z = dz;
}

void Model::setRotation(float dx, float dy, float dz)
{
	rotation.x = dx;
	rotation.y = dy;
	rotation.z = dz;
}

unsigned int Model::getVAO()
{
	return VAO;
}

unsigned int Model::getID()
{
	return modelId;
}
