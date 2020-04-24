#pragma once

#include "ivsEngine.h"

class Render {
private:
	render_mode renderMode;
	float FOV;
	float NEAR_PLANE;
	float FAR_PLANE;
	float hOrthoFactor;

private:
	Render() {}

	static Render& get();
	
	void renderModels();

public:
	static void render();
};