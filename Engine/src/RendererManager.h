#pragma once

#include "ModelManager.h"
#include "ShaderManager.h"
#include "DisplayManager.h"


class RendererManager {
private:
	ModelManager* modelsRef;
	ShaderManager* shadersRef;
	DisplayManager* displayRef;

public:
	RendererManager(ModelManager& models, ShaderManager& shader, DisplayManager& display) 
		: modelsRef(&models), shadersRef(&shader), displayRef(&display) {}

	void render();

	friend class ModelManager;
};
