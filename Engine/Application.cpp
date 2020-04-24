#include "Display.h"
#include "Shaders.h"
#include "Models.h"
#include "Render.h"
#include "Camera.h"

int main()
{
	Display::init(800, 600);

	Shaders::addShaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	Shaders::addShaders("res/shaders/guiVertex.shader", "res/shaders/guiFragment.shader");

	Model* model = Models::addObjModel("res/models/cube.model");

	while (Display::isOpen()) {
		Display::prepare();

		model->rotate(0.1f, 0.1f, 0.1f);

		Render::render();

		Camera::update();

		Display::update();
	}

	Shaders::terminate();
	Display::terminate();
	return 0;
}