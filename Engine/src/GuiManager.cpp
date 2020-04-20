#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GuiManager.h"
#include "ModelManager.h"


glm::vec3 GuiManager::mainColor = glm::vec3(0.3f, 0.5f, 0.8f);

unsigned int GuiManager::padding = 50;


guiElement::guiElement(gui_element_align elementAlign, unsigned int pad, unsigned int sizeX, unsigned int sizeY, glm::vec3 color, guiElement* parent = nullptr)
	: align(elementAlign), padding(pad), sizeX(sizeX), sizeY(sizeY), color(color), parent(parent) {}

guiElement::guiElement(unsigned int posX, unsigned int posY, unsigned int sizeX, unsigned int sizeY, glm::vec3 color, guiElement* parent = nullptr)
	: posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY), color(color), parent(parent) {}


void GuiManager::render()
{
	int width, height;
	glfwGetFramebufferSize(displayRef->window, &width, &height);

	update(width, height);

	glUseProgram(shadersRef->guiShaderProgram);
	glBindVertexArray(guiVAO);
	
	for (auto element : guiElements) {
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::ortho(0.0f, (float) width, 0.0f, (float) height, 0.0f, 0.1f);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(element->posX, element->posY, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(element->sizeX, element->sizeY, 0.0f));

		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "model"), modelMatrix);
		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "projection"), projectionMatrix);
		shadersRef->setUniform3f(glGetUniformLocation(shadersRef->guiShaderProgram, "color"), element->color);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

void GuiManager::update(int width, int height) {
	if (glfwGetKey(displayRef->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		padding += 1;

	if (glfwGetKey(displayRef->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		padding -= 1;

	for (auto element : guiElements)
	{
		int sizeX = element->sizeX;
		int sizeY = element->sizeY;

		switch (element->align) {
		case NK_GUI_CENTER:
			element->posX = width / 2;
			element->posY = height / 2;
			break;
		case NK_GUI_TOPL:
			element->posX = sizeX / 2 + padding;
			element->posY = height - sizeY / 2 - padding;
			break;
		case NK_GUI_TOPC:
			element->posX = width / 2;
			element->posY = height - sizeY / 2 - padding;
			break;
		case NK_GUI_TOPR:
			element->posX = width - sizeX / 2 - padding;
			element->posY = height - sizeY / 2 - padding;
			break;
		case NK_GUI_BOTL:
			element->posX = sizeX / 2 + padding;
			element->posY = sizeY / 2 + padding;
			break;
		case NK_GUI_BOTC:
			element->posX = width / 2;
			element->posY = sizeY / 2 + padding;
			break;
		case NK_GUI_BOTR:
			element->posX = width - sizeX / 2 - padding;
			element->posY = sizeY / 2 + padding;
			break;
		case NK_GUI_LEFC:
			element->posX = sizeX / 2 + padding;
			element->posY = height / 2;
			break;
		case NK_GUI_RIGC:
			element->posX = width - sizeX / 2 - padding;
			element->posY = height / 2;
			break;
		}
	}
}


unsigned int GuiManager::createVAO()
{
	int positions[] = { -1, 1, -1,-1, 1, 1, 1,-1 };

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(int), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(int), (void*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}

void GuiManager::createWindow(gui_element_align align, unsigned int elementWidth, unsigned int elementHeight, glm::vec3 color = mainColor)
{
	guiElement* element = new guiElement(align, padding, elementWidth, elementHeight, color);
	guiElements.emplace_back(element);
}

GuiManager::GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& cameraRef, ShaderManager& shaderRef)
	: modelsRef(&modelsRef), displayRef(&displayRef), cameraRef(&cameraRef), shadersRef(&shaderRef)
{
	guiVAO = createVAO();

	createWindow(NK_GUI_TOPL, 50, 50);
	createWindow(NK_GUI_TOPR, 50, 50, glm::vec3(1.0f, 0.0f, 0.0f));

	createWindow(NK_GUI_BOTL, 50, 50);
	createWindow(NK_GUI_BOTR, 50, 50);

	createWindow(NK_GUI_RIGC, 50, 50);
	createWindow(NK_GUI_LEFC, 50, 50, glm::vec3(1.0f, 1.0f, 0.0f));

	createWindow(NK_GUI_TOPC, 50, 50);
	createWindow(NK_GUI_BOTC, 50, 50);
	createWindow(NK_GUI_CENTER, 50, 50);

	int width, height;
	glfwGetFramebufferSize(displayRef.window, &width, &height);
	update(width, height);
}