#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RendererManager.h"

int RendererManager::hOrthoFactor = 10;

void RendererManager::render() {
	glUseProgram(shadersRef->modelsShaderProgram);

	for (auto model : modelsRef->models) {
		if (model.second->type == NK_NOTGUI) {
			glBindVertexArray(model.second->VAO);
			
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			glm::mat4 projectionMatrix = glm::mat4(1.0f);

			int width, height;
			glfwGetFramebufferSize(displayRef->window, &width, &height);
			float ratio = (float)width / (float)height;
			
			if (displayRef->MODE == NK_PERSPECTIVE) {
				projectionMatrix = glm::perspective(glm::radians(displayRef->FOV), ratio, displayRef->NEAR_PLANE, displayRef->FAR_PLANE);
			}
			else
			{
				projectionMatrix = glm::ortho((float)-hOrthoFactor * ratio, (float)hOrthoFactor * ratio, (float)-hOrthoFactor, (float)hOrthoFactor, displayRef->NEAR_PLANE, displayRef->FAR_PLANE);
			}

			modelMatrix = glm::translate(modelMatrix, model.second->position);
			modelMatrix = glm::rotate(modelMatrix, model.second->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, model.second->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, model.second->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			modelMatrix = glm::scale(modelMatrix, model.second->scaleFactor);

			shadersRef->setUniformM4(glGetUniformLocation(shadersRef->modelsShaderProgram, "model"), modelMatrix);
			shadersRef->setUniformM4(glGetUniformLocation(shadersRef->modelsShaderProgram, "projection"), projectionMatrix);
			
			glDrawElements(GL_TRIANGLES, model.second->indexCount, GL_UNSIGNED_INT, 0);
		}
	}
}