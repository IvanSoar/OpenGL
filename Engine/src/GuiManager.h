#pragma once

#include "ModelManager.h"
#include "DisplayManager.h"

#include <map>
#include <vector>

struct guiWindow {
	unsigned int padding;
	gui_window_align align;
	unsigned int sizeX, sizeY;
	unsigned int posX, posY;
};

class GuiManager{
protected:
	ModelManager* modelManagerRef;
	DisplayManager* displayManagerRef;

public:
	GuiManager(ModelManager& modelsRef, DisplayManager& displayRef);
	void createWindow(int padding, gui_window_align align, int sizeX, int sizeY = 0);
};