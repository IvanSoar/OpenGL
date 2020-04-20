#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class ShaderManager{
private:
	const char* SHADER_DIR = "res/shaders/";
	const char* SHADER_EXT = ".shader";

	unsigned int transUniformeLoc;
	unsigned int projUniformeLoc;


protected:
	unsigned int modelsShaderProgram;
	unsigned int guiShaderProgram;

	friend class RendererManager;
	friend class CameraManager;
	friend class GuiManager;

public:
	ShaderManager();

	unsigned int createShaderProgram(const std::string& vertex, const std::string& fragment);
	
	std::string loadShader(std::string filename);
	void setUniformM4(int location, glm::mat4 value);
};