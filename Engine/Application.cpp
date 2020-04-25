#include "Display.h"
#include "Shaders.h"
#include "Models.h"
#include "Render.h"
#include "Camera.h"
#include "Controller.h"
#include "UserInterface.h"

int main()
{
	Display::init(800, 600);
	Controller::init();

	Shaders::addShaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	Shaders::addShaders("res/shaders/guiVertex.shader", "res/shaders/guiFragment.shader");

	Model* model = Models::addObjModel("res/models/cube.model");

	UserInterface::slider(0, 0, 200, config::clearColor.r, 0, 1, 0.1f);
	UserInterface::slider(0, 50, 200, config::clearColor.g, 0, 1, 0.1f);
	UserInterface::slider(0, 100, 200, config::clearColor.b, 0, 1, 0.1f);
	UserInterface::slider(0, 150, 200, config::cameraPos.z, -100, 100, 1);
	UserInterface::slider(0, 200, 200, config::cameraPos.x, -5, 5, 1);
	UserInterface::slider(0, 250, 200, config::cameraPos.y, -5, 5, 1);
	UserInterface::slider(0, 350, 200, config::fov, 0, 180, 5);

	//UserInterface::button(50, 350, 50, 50, config::vSync);

	float value = 0.0f;
	UserInterface::slider(0, 300, 200, value, -0.3, 0.3, 0.1f);

	while (Display::isOpen()) {
		Display::prepare();

		model->rotate(value, value, value);

		Render::render();

		Camera::update();

		Display::update();
	}

	Shaders::terminate();
	Display::terminate();
	return 0;
}