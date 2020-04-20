#include "glad/glad.h"

#include "DisplayManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "RendererManager.h"
#include "CameraManager.h"
#include "GuiManager.h"
#include "Utils.h"

#include <ctime>

int main()
{
	DisplayManager display;
	ShaderManager shaders;
	ModelManager models;
	CameraManager camera(shaders);
	GuiManager gui(models, display, camera, shaders);
	RendererManager renderer(models, shaders, display, gui);

	models.add("cube");
	int cubo1 = models.getLast();

	models.add("cube");
	int cubo2 = models.getLast();

	models.add("cube");
	int cubo3 = models.getLast();

	models.add("cube");
	int cubo4 = models.getLast();

	models.add("cube");
	int cubo5 = models.getLast();
	
	models.add("cube");
	int cubo6 = models.getLast();

	srand(time(0));
	models.getModel(cubo1).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);
	models.getModel(cubo2).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);
	models.getModel(cubo3).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);
	models.getModel(cubo4).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);
	models.getModel(cubo5).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);
	models.getModel(cubo6).setPosition(rand() % 10 - 5.0f, rand() % 10 - 5.0f, rand() % 10 - 5.0f);

	while (display.isOpen())
	{
		display.processInputs(&camera, &renderer);

		display.prepare();

		models.getModel(cubo1).rotate(0.01f, 0.01f, 0.01f);
		models.getModel(cubo2).rotate(0.01f, 0.01f, 0.01f);
		models.getModel(cubo3).rotate(0.01f, 0.01f, 0.01f);
		models.getModel(cubo4).rotate(0.01f, 0.01f, 0.01f);
		models.getModel(cubo5).rotate(0.01f, 0.01f, 0.01f);
		models.getModel(cubo6).rotate(0.01f, 0.01f, 0.01f);

		camera.update();
		
		renderer.render();
		
		gui.render();

		display.update();
	}

	display.destroy();
	return 0;
}