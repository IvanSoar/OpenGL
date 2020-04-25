#include "GLAD/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <fstream>
#include <string>

#include "Shaders.h"
#include "ivsEngine.h"

Shaders& Shaders::get()
{
	static Shaders instance;
	return instance;
}

void Shaders::addShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	unsigned int vertexShader = get().createShader(vertexFilePath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = get().createShader(fragmentFilePath, GL_FRAGMENT_SHADER);

	get().createShaderProgram(vertexShader, fragmentShader);
}

unsigned int Shaders::createShader(const std::string& filePath, GLenum type)
{
	std::string buffer;

	buffer = loadShader(filePath);
	const char* shaderSource = buffer.c_str();

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, 0);
	glCompileShader(shader);

	checkShader(shader);
		
	return shader;
}

std::string Shaders::loadShader(const std::string& filepath)
{
	std::ifstream file;
	std::string code;
	std::stringstream stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filepath);

		stream << file.rdbuf();
		code = stream.str();

		file.close();
	}
	catch (std::ifstream::failure& e) {
		ivs::log("Loading Shader", 0);
		ivs::log(filepath);
		ivs::log(e.what());
	}

	return code;
}

void Shaders::checkShader(unsigned int shader)
{
	GLint success;
	GLchar infolog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infolog);
		ivs::log("shader", success);
		ivs::log(infolog);
	}
}

void Shaders::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	GLint success;
	GLchar infolog[1024];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infolog);
		ivs::log("Shader program creation", success);
		ivs::log(infolog);
	}

	glDetachShader(shaderProgram, vertexShader);
	glDeleteShader(vertexShader);

	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(fragmentShader);

	shaderProgramList.push_back(shaderProgram);
}

void Shaders::setUniformM4(int location, glm::mat4 value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shaders::setUniform3f(int location, glm::vec3 value)
{
	glUniform3fv(location, 1, &value[0]);
}

void Shaders::terminate()
{
	for (auto program : get().shaderProgramList)
		glDeleteProgram(program);
}

void Shaders::activate(unsigned int shaderProgram)
{
	glUseProgram(get().shaderProgramList[shaderProgram]);
}

std::vector<unsigned int> Shaders::getShaders()
{
	return get().shaderProgramList;
}


