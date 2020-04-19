#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RendererManager.h"

#include <math.h>

void RendererManager::render() {
	for (auto model : modelsRef->models) {
		glBindVertexArray(model.second->VAO);

		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);


		int width, height;
		glfwGetFramebufferSize(displayRef->window, &width, &height);

		float ratio = (float)width / (float)height;
		if (displayRef->MODE == NK_PERSPECTIVE && model.second->type == NK_NOTGUI && state == NK_GAME) {
			projectionMatrix = glm::perspective(glm::radians(displayRef->FOV), ratio, 0.01f, 100.0f);
		}
		else if (state == NK_MENU)
		{
			projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
			shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "view"), viewMatrix);
		}

		modelMatrix = glm::translate(modelMatrix, model.second->position);
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, model.second->scaleFactor);

		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "projection"), projectionMatrix);
		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "model"), modelMatrix);


		glDrawElements(GL_TRIANGLES, model.second->indexCount, GL_UNSIGNED_INT, 0);
	}
}