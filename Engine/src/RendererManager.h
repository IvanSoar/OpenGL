#pragma once

#include "ModelManager.h"
#include "ShaderManager.h"
#include "DisplayManager.h"
#include "Utils.h"

class RendererManager {
private:
	ModelManager* modelsRef;
	ShaderManager* shadersRef;
	DisplayManager* displayRef;

	static int hOrthoFactor;

public:
	game_state state;

public:
	RendererManager(ModelManager& models, ShaderManager& shader, DisplayManager& display) 
		: modelsRef(&models), shadersRef(&shader), displayRef(&display), state(NK_GAME) {}

	void render();

	friend class ModelManager;
};
