#include "DisplayManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "RendererManager.h"

int main()
{
	DisplayManager display;
	ShaderManager shaders;
	ModelManager models;

	RendererManager renderer(models, shaders, display);

	models.add("cube");
	models.getModel("cube").setPosition(0.0f, 0.0f, 0.0f);

	while (display.isOpen())
	{
		display.prepare();

		shaders.start();

		models.getModel("cube").rotate(0.01f, 0.01f, 0.01f);

		renderer.render();

		display.update();
	}

	display.destroy();
	return 0;
}