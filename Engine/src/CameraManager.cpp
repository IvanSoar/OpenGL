#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "CameraManager.h"

void CameraManager::update()
{
	glUseProgram(shadersRef->modelsShaderProgram);

	glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	shadersRef->setUniformM4(glGetUniformLocation(shadersRef->modelsShaderProgram, "view"), viewMatrix);
}
