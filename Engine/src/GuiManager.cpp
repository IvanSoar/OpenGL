#include "glad/glad.h"

#include "GuiManager.h"
#include "ModelManager.h"

GuiManager::GuiManager(ModelManager& modelsRef, DisplayManager& displayRef)
	: modelManagerRef(&modelsRef), displayManagerRef(&displayRef)
{
	createWindow(10, NK_TOPL, 50, 50);
	createWindow(10, NK_TOPC, 50, 50);
	createWindow(10, NK_TOPR, 50, 50);
	createWindow(10, NK_BOTL, 50, 50);
	createWindow(10, NK_BOTC, 50, 50);
	createWindow(10, NK_BOTR, 50, 50);
	createWindow(10, NK_LEFC, 50, 50);
	createWindow(10, NK_RIGC, 50, 50);
	createWindow(10, NK_CENTER, 200, 200);
}

void GuiManager::createWindow(int padding, gui_window_align align, int sizeX, int sizeY)
{
	int posX = 0, posY = 0;

	int width, height;
	glfwGetFramebufferSize(displayManagerRef->window, &width, &height);

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

	modelManagerRef->add("quad", NK_GUI);
	unsigned int ID = modelManagerRef->getLast();
	modelManagerRef->getModel(ID).scale((float)sizeX, (float)sizeY, 0.0f);
	modelManagerRef->getModel(ID).setPosition(posX, posY, 0.0f);
}