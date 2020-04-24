#pragma once

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shaders.h"

Camera& Camera::get()
{
	static Camera instance;
	return instance;
}

void Camera::update()
{
	Shaders::activate(0);

	glm::mat4 viewMatrix = glm::lookAt(get().cameraPos, get().cameraPos + get().cameraFront, get().cameraUp);

	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[0], "view"), viewMatrix);
}
