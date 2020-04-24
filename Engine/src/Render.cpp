#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Render.h"
#include "Display.h"
#include "Models.h"
#include "Shaders.h"

Render& Render::get()
{
	static Render instance;
	instance.renderMode = IVS_PERSP_MODE;
	instance.FOV = 70.0f;
	instance.NEAR_PLANE = 0.1f;
	instance.FAR_PLANE = 100.0f;
	return instance;
}

void Render::renderModels()
{
	for (auto model : Models::getModels()) {
		glBindVertexArray(model->getVAO());

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);

		int width, height;
		glfwGetFramebufferSize(Display::getWindow(), &width, &height);
		float ratio = (float)width / (float)height;

		if (get().renderMode == IVS_PERSP_MODE) {
			projectionMatrix = glm::perspective(glm::radians(get().FOV), ratio, get().NEAR_PLANE, get().FAR_PLANE);
		}
		else
		{
			projectionMatrix = glm::ortho(-get().hOrthoFactor * ratio, get().hOrthoFactor * ratio, -get().hOrthoFactor, get().hOrthoFactor, get().NEAR_PLANE, get().FAR_PLANE);
		}

		modelMatrix = glm::translate(modelMatrix, model->position);
		modelMatrix = glm::rotate(modelMatrix, model->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, model->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, model->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, model->scaleFactor);

		Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[0], "model"), modelMatrix);
		Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[0], "projection"), projectionMatrix);

		glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
	}
}

void Render::render()
{
	Shaders::activate(0);
	get().renderModels();
}
