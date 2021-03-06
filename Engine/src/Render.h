#pragma once

#include "../ivsEngine.h"

class Render {
private:
	Render() {}

	static Render& get();
	
	static void renderModels();
	static void renderUi();
	static void renderTerrain();
	static void renderText();

public:
	static void render();
};