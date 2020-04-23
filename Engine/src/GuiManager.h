#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ModelManager.h"
#include "ShaderManager.h"
#include "DisplayManager.h"

#include <map>
#include <vector>

class guiElement{
protected:
	int x, y;
	int width, height;

	gui_element_align align;

	glm::vec3 color;
	
	guiElement* parent;

protected:
	guiElement(int x, int y, int width, int height, glm::vec3 colour, guiElement* related, gui_element_align align);
	
	friend class GuiManager;
	friend class slider;
};

class GuiManager{
protected:
	DisplayManager* displayRef;
	CameraManager* cameraRef;
	ShaderManager* shadersRef;
	
	static glm::vec3 mainColor;
	unsigned int padding = 10;
	bool state = false;

	unsigned int guiVAO;

	std::vector<std::pair<gui_element_type, guiElement*>> guiElements;
	
	friend class slider;

public:
	GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& cameraRef, ShaderManager& shaderRef);

	unsigned int createVAO();

	void render();
	void update(std::pair<gui_element_type, guiElement*> element, int width, int height);

	guiElement* window(gui_element_align align, int width, int height, guiElement* parent);
	guiElement* slider(int x, int y, int size, guiElement* parent, float* value);

	bool isMouseOver(int x, int y, int width, int height);
	bool isButtonDown(int mouseButton);
};