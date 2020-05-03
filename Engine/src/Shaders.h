#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

class Shaders
{
private:
	std::vector<unsigned int> shaderProgramList;

	unsigned int projUniformeLoc;
	unsigned int transUniformeLoc;

private:
	Shaders() {}

	static Shaders& get();

	void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	std::string loadShader(const std::string& filename);
	unsigned int createShader(const std::string& filename, GLenum type);
	void checkShader(unsigned int shader);

public:
	static void addShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	
	static std::vector<unsigned int> getShaders();
	
	static void activate(unsigned int shaderProgram);

	static void setUniformM4(int location, glm::mat4 value);
	static void setUniform3f(int location, glm::vec3 value);
	static void setUniform4f(int location, glm::vec4 value);
	static void setUniform1i(int location, int value);

	static void terminate();
};