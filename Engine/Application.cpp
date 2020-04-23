#include "glad/glad.h"

#include "DisplayManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "RendererManager.h"
#include "CameraManager.h"
#include "Utils.h"

#include <ctime>

int main()
{
	DisplayManager display;
	ShaderManager shaders;
	ModelManager models;
	CameraManager camera(shaders);
	RendererManager renderer(models, shaders, display);

	models.add("cube");
	int cubo1 = models.getLast();

	while (display.isOpen())
	{
		display.processInputs(&camera, &renderer);

		display.prepare();

		models.getModel(cubo1).rotate(0.01f, 0.01f, 0.01f);

		camera.update();
		
		renderer.render();
		
		display.update();
	}

	display.destroy();
	return 0;
}