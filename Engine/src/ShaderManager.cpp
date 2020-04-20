#include "GLAD/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include "Utils.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager(){
	modelsShaderProgram = createShaderProgram("vertex", "fragment");
	guiShaderProgram = createShaderProgram("guiVertex", "guiFragment");
}

unsigned int ShaderManager::createShaderProgram(const std::string& vertex, const std::string& fragment)
{
	std::string buffer1, buffer2;

	buffer1 = loadShader(vertex);
	const char* vertexShaderSource = buffer1.c_str();

	buffer2 = loadShader(fragment);
	const char* fragmentShaderSource = buffer2.c_str();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "não compilou vertex shader" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << "não compilou fragment shader" << std::endl;
		std::cout << infoLog << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
		std::cout << "não linkou shader program" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::string ShaderManager::loadShader(std::string filename)
{
	std::ifstream file;
	std::string code;
	std::stringstream stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(SHADER_DIR + filename + SHADER_EXT);
		
		stream << file.rdbuf();
		code = stream.str();
		
		file.close();
	}
	catch (std::ifstream::failure& e) {
		nk::Log("Loading Shader", 0);
		nk::Log(filename);
		nk::Log(e.what());
	}

	return code;
}

void ShaderManager::setUniformM4(int location, glm::mat4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}