#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <string>

#include "Models.h"

Models& Models::get()
{
	static Models instance;
	return instance;
}

rawModel Models::loadModel(const std::string& filepath)
{
	float v1, v2, v3, v4, v5, v6;
	unsigned int i1, i2, i3;
	unsigned int vertex = 0;
	unsigned int index = 0;

	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;

	std::ifstream file(filepath, std::ifstream::in);
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

Model* Models::addObjModel(const std::string& filepath)
{
	rawModel* model = new rawModel(get().loadModel(filepath));

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertexCount * 6 * sizeof(float), model->vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), model->indexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Model* modelData = new Model(VAO, model->vertexCount, model->indexCount);
	get().modelsList.emplace_back(modelData);

	delete model;
	return modelData;
}

std::vector<Model*> Models::getModels()
{
	return get().modelsList;
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

unsigned int Model::getVertexCount()
{
	return vertexCount;
}

unsigned int Model::getIndexCount()
{
	return indexCount;
}
