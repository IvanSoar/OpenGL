#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <vector>
#include <string>

class RawModel {

protected:
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	unsigned int vertexCount;
	unsigned int indexCount;
	
	friend class ModelManager;

public:
	RawModel(std::vector<float> vertexD, std::vector<unsigned int> indexD, unsigned int vertexC, unsigned int indexC)
		: vertexData(vertexD), indexData(indexD), vertexCount(vertexC), indexCount(indexC) {}
};

class Model {
private:
	unsigned int modelId;
	std::string ModelName;

protected:
	unsigned int VAO;
	unsigned int vertexCount;
	unsigned int indexCount;

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scaleFactor = glm::vec3(1.0f);

	friend class RendererManager;

public:
	Model(unsigned int id, const std::string& name, unsigned int vao, unsigned int vertexCount, unsigned int indexCount)
		: modelId(id), ModelName(name), VAO(vao), vertexCount(vertexCount), indexCount(indexCount) {}

	void move(float dx, float dy, float dz);
	void rotate(float dx, float dy, float dz);
	void scale(float value);
	void scale(float dx, float dy, float dz);
	void setPosition(float dx, float dy, float dz);
	void setRotation(float dx, float dy, float dz);

	unsigned int getVAO();
};

class ModelManager {
private:
	const std::string MODELS_DIR = "res/models/";
	const std::string MODELS_EXT = ".model";

protected:
	std::map<std::string, Model*> models;

	friend class RendererManager;

public:
	void add(const std::string& filename);
	Model& getModel(const std::string& modelName);

private:
	RawModel loadModel(const std::string& filename);
	unsigned int generateModelId();
};


