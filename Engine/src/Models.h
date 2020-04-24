#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

class rawModel {
protected:
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	unsigned int vertexCount;
	unsigned int indexCount;

	friend class Models;

public:
	rawModel(std::vector<float> vertex, std::vector<unsigned int> index, unsigned int vCount, unsigned int iCount) 
		: vertexData(vertex), indexData(index), vertexCount(vCount), indexCount(iCount) {}
};

class Model {
private:
	unsigned int VAO;
	unsigned int vertexCount;
	unsigned int indexCount;

protected:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scaleFactor = glm::vec3(1.0f);

	friend class Render;

public:
	Model(unsigned int vao, unsigned int vCount, unsigned int iCount) 
		: VAO(vao), vertexCount(vCount), indexCount(iCount) {}

	void move(float dx, float dy, float dz);
	void rotate(float dx, float dy, float dz);
	void scale(float value);
	void scale(float dx, float dy, float dz);
	void setPosition(float dx, float dy, float dz);
	void setRotation(float dx, float dy, float dz);
	
	unsigned int getVAO();
	unsigned int getVertexCount();
	unsigned int getIndexCount();
};

class Models {
private:
	std::vector<Model*> modelsList;

private:
	Models() {}

	static Models& get();

	rawModel loadModel(const std::string& filepath);

public:
	static Model* addObjModel(const std::string& filepath);
	static std::vector<Model*> getModels();
};