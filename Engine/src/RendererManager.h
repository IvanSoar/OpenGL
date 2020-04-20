#pragma once

#include "ModelManager.h"
#include "ShaderManager.h"
#include "DisplayManager.h"
#include "GuiManager.h"
#include "Utils.h"

class RendererManager {
private:
	ModelManager* modelsRef;
	ShaderManager* shadersRef;
	DisplayManager* displayRef;
	GuiManager* guiRef;

	static int hOrthoFactor;

public:
	game_state state;

public:
	RendererManager(ModelManager& models, ShaderManager& shader, DisplayManager& display, GuiManager& gui) 
		: modelsRef(&models), shadersRef(&shader), displayRef(&display), guiRef(&gui), state(NK_GAME) {}

	void render();

	friend class ModelManager;
};
