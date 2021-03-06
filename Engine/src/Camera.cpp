#pragma once

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shaders.h"
#include "../ivsEngine.h"

Camera& Camera::get()
{
	static Camera instance;
	return instance;
}

void Camera::update()
{
	glm::mat4 viewMatrix = glm::lookAt(config::cameraPos, config::cameraPos + config::cameraFront, config::cameraUp);

	Shaders::activate(0);
	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[0], "view"), viewMatrix);

	Shaders::activate(2);
	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[2], "view"), viewMatrix);
}
