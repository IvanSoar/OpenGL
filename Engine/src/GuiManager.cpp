#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GuiManager.h"
#include "ModelManager.h"

GuiManager::GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& camRef, ShaderManager& shaderRef)
	: modelsRef(&modelsRef), displayRef(&displayRef), cameraRef(&camRef), shadersRef(&shaderRef)
{
	createWindow(NK_CENTER, 50, 50);
	createWindow(NK_TOPL, 50, 50);
	createWindow(NK_TOPC, 50, 50);
	createWindow(NK_TOPR, 50, 50);
	createWindow(NK_BOTL, 50, 50);
	createWindow(NK_BOTC, 50, 50);
	createWindow(NK_BOTR, 50, 50);
	createWindow(NK_LEFC, 50, 50);
	createWindow(NK_RIGC, 50, 50);
}

void GuiManager::createWindow(gui_window_align align, int sizeX, int sizeY)
{
	int posX = 0, posY = 0;

	int width, height;
	glfwGetFramebufferSize(displayRef->window, &width, &height);

	switch (align) {
	case NK_CENTER:
		posX = width / 2;
		posY = height / 2;
		break;
	case NK_TOPL:
		posX = sizeX / 2 + padding;
		posY = height - sizeY / 2 - padding;
		break;
	case NK_TOPC:
		posX = width / 2;
		posY = height - sizeY / 2 - padding;
		break;
	case NK_TOPR:
		posX = width - sizeX / 2 - padding;
		posY = height - sizeY / 2 - padding;
		break;
	case NK_BOTL:
		posX = sizeX / 2 + padding;
		posY = sizeY / 2 + padding;
		break;
	case NK_BOTC:
		posX = width / 2;
		posY = sizeY / 2 + padding;
		break;
	case NK_BOTR:
		posX = width - sizeX / 2 - padding;
		posY = sizeY / 2 + padding;
		break;
	case NK_LEFC:
		posX = sizeX / 2 + padding;
		posY = height / 2;
		break;
	case NK_RIGC:
		posX = width - sizeX / 2 - padding;
		posY = height / 2;
		break;
	}

	modelsRef->add("quad", NK_GUI);
	unsigned int ID = modelsRef->getLast();

	modelsRef->getModel(ID).setPosition((float) posX, (float) posY, 0.0f);
	modelsRef->getModel(ID).scale((float)sizeX, (float)sizeY, 0.0f);
}

void GuiManager::render()
{
	int width, height;
	glfwGetFramebufferSize(displayRef->window, &width, &height);

	glUseProgram(shadersRef->guiShaderProgram);
	
	for (auto model : modelsRef->models) {
		if (model.second->type == NK_GUI) {
			glBindVertexArray(model.second->VAO);

			glm::mat4 projectionMatrix = glm::mat4(1.0f);
			projectionMatrix = glm::ortho(0.0f, (float) width, 0.0f, (float) height, 0.0f, 0.1f);

			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, model.second->position);
			modelMatrix = glm::scale(modelMatrix, model.second->scaleFactor);

			shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "model"), modelMatrix);
			shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "projection"), projectionMatrix);

			glDrawElements(GL_TRIANGLES, model.second->indexCount, GL_UNSIGNED_INT, 0);
		}
	}
}


