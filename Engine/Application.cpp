#include "Display.h"
#include "Shaders.h"
#include "Models.h"
#include "Render.h"
#include "Camera.h"
#include "Controller.h"
#include "Terrain.h"
#include "UserInterface.h"

int main()
{
	Display::init();

	Shaders::addShaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	Shaders::addShaders("res/shaders/guiVertex.shader", "res/shaders/guiFragment.shader");
	Shaders::addShaders("res/shaders/terrainVertex.shader", "res/shaders/terrainFragment.shader");

	Model* model = Models::addObjModel("res/models/cube.model");
	model->setPosition(0, 1, 0);

	Controller::init();
	UserInterface::init();

	UserInterface::slider(0, 0, 200, config::clearColor.r, 0, 1, 0.1f);
	UserInterface::slider(0, 50, 200, config::clearColor.g, 0, 1, 0.1f);
	UserInterface::slider(0, 100, 200, config::clearColor.b, 0, 1, 0.1f);
	UserInterface::slider(0, 150, 200, config::cameraSpeed, 0.1, 3.0, 0.1f);
	
	float value = 0.0f;
	UserInterface::slider(0, 200, 200, value, -0.3, 0.3, 0.1f);

	float r = 1.0f, g = 0.5f, b = 0.3f;
	/*UserInterface::slider(0, 250, 200, r, 0, 1, 0.1f);
	UserInterface::slider(0, 300, 200, g, 0, 1, 0.1f);
	UserInterface::slider(0, 350, 200, b, 0, 1, 0.1f);*/

	Terrain::generate();

	while (Display::isOpen()) {
		Controller::processInputs();

		Display::prepare();

		model->rotate(value, value, value);
		Terrain::changeColor(r, g, b, 1.0f);

		Render::render();

		Camera::update();

		Display::update();
	}

	Shaders::terminate();
	Display::terminate();
	return 0;
}