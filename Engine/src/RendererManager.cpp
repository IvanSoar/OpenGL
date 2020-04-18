#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RendererManager.h"

void RendererManager::render() {
	for (auto model : modelsRef->models) {
		glBindVertexArray(model.second->VAO);

		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

		modelMatrix = glm::translate(modelMatrix, model.second->position);
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.x, glm::vec3(1.0f, 0.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.y, glm::vec3(0.0f, 1.0, 0.0));
		modelMatrix = glm::rotate(modelMatrix, model.second->rotation.z, glm::vec3(0.0f, 0.0, 1.0));
		modelMatrix = glm::scale(modelMatrix, model.second->scaleFactor);

		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "projection"), projectionMatrix);
		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "view"), viewMatrix);
		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->shaderProgram, "model"), modelMatrix);

		glDrawElements(GL_TRIANGLES, model.second->indexCount, GL_UNSIGNED_INT, 0);
	}
}
