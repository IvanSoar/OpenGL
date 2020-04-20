#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ModelManager.h"
#include "ShaderManager.h"
#include "DisplayManager.h"

#include <map>
#include <vector>

class guiElement {
protected:
	gui_element_align align;
	unsigned int padding;
	glm::vec3 color;
	
	unsigned int posX, posY;
	unsigned int sizeX, sizeY;

	guiElement* parent;

	friend class GuiManager;

public:
	guiElement(gui_element_align elementAlign, unsigned int pad, unsigned int sizeX, unsigned int sizeY, glm::vec3 color, guiElement* parent);
	guiElement(unsigned int posX, unsigned int posY, unsigned int sizeX, unsigned int sizeY, glm::vec3 color, guiElement* parent);
};

class GuiManager{
protected:
	ModelManager* modelsRef;
	DisplayManager* displayRef;
	CameraManager* cameraRef;
	ShaderManager* shadersRef;
	
	static glm::vec3 mainColor;
	static unsigned int padding;

	unsigned int guiVAO;

	std::vector<guiElement*> guiElements;

public:
	GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& cameraRef, ShaderManager& shaderRef);

	unsigned int createVAO();

	void createWindow(gui_element_align align, unsigned int elementWidth, unsigned int elementHeight, glm::vec3 color);

	void update(int width, int height);
	void render();
};