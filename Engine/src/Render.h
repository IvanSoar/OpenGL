#pragma once

#include "../ivsEngine.h"

class Render {
private:
	Render() {}

	static Render& get();
	
	void renderModels();
	void renderUi();

public:
	static void init();
	static void render();
};