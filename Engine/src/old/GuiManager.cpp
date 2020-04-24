#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GuiManager.h"
#include "ModelManager.h"
#include "Utils.h"

glm::vec3 GuiManager::mainColor = glm::vec3(1.0f, 0.5f, 0.8f);


guiElement::guiElement(int x, int y, int width, int height, glm::vec3 color, guiElement* parent, gui_element_align align = NK_GUI_FREE)
	: x(x), y(y), width(width), height(height), color(color), parent(parent), align(align) {}



void GuiManager::render()
{
	int width, height;
	glfwGetFramebufferSize(displayRef->window, &width, &height);

	glUseProgram(shadersRef->guiShaderProgram);
	glBindVertexArray(guiVAO);
	
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(0.0f, (float)width, (float) height, 0.0f, 0.0f, 0.1f);
	shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "projection"), projectionMatrix);

	if (glfwGetKey(displayRef->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		padding += 1;

	if (glfwGetKey(displayRef->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		padding -= 1;

	for (auto element : guiElements) {
		update(element, width, height);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(element.second->x, element.second->y, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(element.second->width, element.second->height, 0.0f));

		shadersRef->setUniformM4(glGetUniformLocation(shadersRef->guiShaderProgram, "model"), modelMatrix);
		shadersRef->setUniform3f(glGetUniformLocation(shadersRef->guiShaderProgram, "color"), element.second->color);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

bool GuiManager::isMouseOver(int x, int y, int width, int height) {
	double xpos, ypos;
	glfwGetCursorPos(displayRef->window, &xpos, &ypos);
	if ((xpos > x - width / 2 && xpos < x + width / 2) && (ypos > y - height / 2 && ypos < y + height / 2))
		return 1;
	return 0;
}

bool GuiManager::isButtonDown(int mouseButton)
{
	return glfwGetMouseButton(displayRef->window, mouseButton) && GLFW_PRESS;
}



void GuiManager::update(std::pair<gui_element_type, guiElement*> element, int width, int height) {
	switch (element.first) {
	case SLIDER_HEAD: 
		double mouseX;
		guiElement* head = element.second;
		guiElement* body = element.second->parent;

		glfwGetCursorPos(displayRef->window, &mouseX, nullptr);

		if (isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			if (isMouseOver(head->x, head->y, head->width, head->height) ||
				isMouseOver(body->x, body->y, body->width, body->height)){
				state = true;
			}
		}
		else {
			state = false;
		}
		
		if(state)
			head->x = (int)mouseX;

		head->x = head->x > body->x + body->width / 2 ? body->x + body->width / 2 : head->x;
		head->x = head->x < body->x - body->width / 2 ? body->x - body->width / 2 : head->x;
		break;
	}
}

guiElement* GuiManager::window(gui_element_align align, int width, int height, guiElement* parent) {
	guiElement* window = new guiElement((width / 2) + padding, (height / 2) + padding, width, height, mainColor, nullptr, align);

	guiElements.emplace_back(WINDOW, window);

	return window;
}

guiElement* GuiManager::slider(int x, int y, int size, guiElement* parent = nullptr, float* value = nullptr)
{
	int proporcion = 20;
	guiElement* body = new guiElement(x + padding + size / 2, y + padding + size / (2 * proporcion), size, size / proporcion, mainColor, parent);
	guiElement* head = new guiElement(body->x, body->y, body->height, body->height * 3, mainColor * 0.5f, body);

	guiElements.emplace_back(SLIDER_HEAD, head, nullptr);
	guiElements.emplace_back(SLIDER_BODY, body, value);

	return head;
}

unsigned int GuiManager::createVAO()
{
	float positions[] = { -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}

GuiManager::GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& cameraRef, ShaderManager& shaderRef)
	: modelsRef(&modelsRef), displayRef(&displayRef), cameraRef(&cameraRef), shadersRef(&shaderRef)
{
	guiVAO = createVAO();

	guiElement* window1 = window(NK_GUI_CENTER, 100, 100, nullptr);
	guiElement* slider1 = slider(100, 100, 200, window1, &cameraRef.cameraSpeed);

	int width, height;
	glfwGetFramebufferSize(displayRef.window, &width, &height);
	for(auto element : guiElements)
		update(element, width, height);
}