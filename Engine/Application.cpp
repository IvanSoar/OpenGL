#include "glad/glad.h"

#include "DisplayManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "RendererManager.h"
#include "CameraManager.h"
#include "GuiManager.h"
#include "Utils.h"

int main()
{
	DisplayManager display;
	ShaderManager shaders;
	ModelManager models;
	CameraManager camera(shaders);
	GuiManager gui(models, display);
	RendererManager renderer(models, shaders, display, gui);

	std::vector<unsigned int> mundo;
	for (int i = 0; i < 10; i++) {
		models.add("cube");
		mundo.push_back(models.getLast());
	}

	for (int i = 0; i < 10; i++) {
		models.getModel(mundo[i]).setPosition((float) i, (float) -i, (float) - i);
	}

	while (display.isOpen())
	{
		for (auto a : mundo) {
			models.getModel(a).rotate(0.01f, 0.01f, 0.01f);
		}

		display.prepare();

		shaders.start();

		display.processInputs(&camera, &renderer);

		camera.update();

		renderer.render();

		display.update();
	}

	display.destroy();
	return 0;
}