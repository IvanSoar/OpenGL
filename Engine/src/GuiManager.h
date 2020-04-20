#pragma once

#include "ModelManager.h"
#include "ShaderManager.h"
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
	ModelManager* modelsRef;
	DisplayManager* displayRef;
	CameraManager* cameraRef;
	ShaderManager* shadersRef;

	int padding = 5;

public:
	GuiManager(ModelManager& modelsRef, DisplayManager& displayRef, CameraManager& camRef, ShaderManager& shaderRef);
	void createWindow(gui_window_align align, int sizeX, int sizeY = 0);
	void render();
};