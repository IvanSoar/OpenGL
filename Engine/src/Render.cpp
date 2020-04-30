#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Render.h"
#include "Display.h"
#include "Models.h"
#include "Shaders.h"
#include "Terrain.h"
#include "UserInterface.h"

Render& Render::get()
{
	static Render instance;
	return instance;
}

void Render::renderModels()
{
	int width, height;
	glfwGetFramebufferSize(Display::getWindow(), &width, &height);
	float ratio = (float)width / (float)height;

	for (auto model : Models::getModels()) {
		glBindVertexArray(model->getVAO());

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);		

		if (config::renderMode) {
			projectionMatrix = glm::perspective(glm::radians(config::fov), ratio, config::nearPlaneP, config::farPlaneP);
		}
		else
		{
			projectionMatrix = glm::ortho(-config::hOrthoFactor * ratio, config::hOrthoFactor * ratio, (float)-config::hOrthoFactor, (float)config::hOrthoFactor, config::nearPlaneO, config::farPlaneO);
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

void Render::renderUi()
{
	glBindVertexArray(UserInterface::getVAO());

	int width, height;
	glfwGetFramebufferSize(Display::getWindow(), &width, &height);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 0.1f);
	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[1], "projection"), projectionMatrix);
	
	for (auto component : UserInterface::getComponents()) {
		component->update();
	}

	for (auto container : UserInterface::getContainers()) {
		container->update();
	}

	for (auto element : UserInterface::getElements()) {

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(element->x, element->y, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(element->width, element->height, 0.0f));

		Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[1], "model"), modelMatrix);
		Shaders::setUniform3f(glGetUniformLocation(Shaders::getShaders()[1], "color"), element->color);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

void Render::renderTerrain()
{
	int width, height;
	glfwGetFramebufferSize(Display::getWindow(), &width, &height);
	float ratio = (float)width / (float)height;

	glBindVertexArray(Terrain::getVAO());

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	if (config::renderMode) {
		projectionMatrix = glm::perspective(glm::radians(config::fov), ratio, config::nearPlaneP, config::farPlaneP);
	}
	else
	{
		projectionMatrix = glm::ortho(-config::hOrthoFactor * ratio, config::hOrthoFactor * ratio, (float)-config::hOrthoFactor, (float)config::hOrthoFactor, config::nearPlaneO, config::farPlaneO);
	}

	modelMatrix = glm::translate(modelMatrix, glm::vec3(Terrain::getX(), 0.0, Terrain::getZ()));
	modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));

	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[2], "model"), modelMatrix);
	Shaders::setUniformM4(glGetUniformLocation(Shaders::getShaders()[2], "projection"), projectionMatrix);

	glDrawElements(GL_TRIANGLES, Terrain::getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Render::render()
{
	Shaders::activate(0);
	renderModels();

	Shaders::activate(1);
	renderUi();

	Shaders::activate(2);
	renderTerrain();
}
