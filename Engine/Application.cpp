#include "Display.h"
#include "Shaders.h"
#include "Models.h"
#include "Render.h"
#include "Camera.h"
#include "Controller.h"
#include "Terrain.h"
#include "Text.h"
#include "UserInterface.h"

int main()
{
	Display::init();

	Shaders::addShaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	Shaders::addShaders("res/shaders/guiVertex.shader", "res/shaders/guiFragment.shader");
	Shaders::addShaders("res/shaders/terrainVertex.shader", "res/shaders/terrainFragment.shader");
	Shaders::addShaders("res/shaders/textVertex.shader", "res/shaders/textFragment.shader");

	Model* model = Models::addObjModel("res/models/cube.model");
	model->setPosition(0, 1, 0);

	Controller::init();
	UserInterface::init();
	TextHandler::loadFont("CandaraASCII");

	UserInterface::panel(IVS_HALIGN_RIGHT);

	UserInterface::slider(config::clearColor.r, 0.0f, 1.0f, 3);
	UserInterface::slider(config::clearColor.g, 0.0f, 1.0f, 3);
	UserInterface::slider(config::clearColor.b, 0.0f, 1.0f, 3);

	UserInterface::slider(config::uiColor.r, 0.0f, 1.0f, 3);
	UserInterface::slider(config::uiColor.g, 0.0f, 1.0f, 3);
	UserInterface::slider(config::uiColor.b, 0.0f, 1.0f, 3);
	UserInterface::slider(config::uiSecondaryColor.a, 0.0f, 1.0f, 3);
	UserInterface::slider(config::cameraSpeed, 0.1f, 3.0f, 2);
	
	UserInterface::slider(config::textWidth, 0.0f, 1.0f, 3);
	UserInterface::slider(config::textEdge, 0.01f, 0.50f, 3);

	float value = 0.0f;
	UserInterface::slider(value, -0.3f, 0.3f, 2);

	/*UserInterface::slider(config::maxVertexperTerrain, 1.0f, 1024.0f, 1.0f);
	UserInterface::slider(config::terrainSize, 1.0f, 1000.0f, 1.0f);*/

	Terrain::generate();
	
	/*TextHandler::text("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce id massa vitae nunc ultrices sodales. "
		"Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Cras ultricies varius dui, scelerisque posuere elit iaculis a. "
		"Fusce sed semper nulla, quis finibus nunc. Vivamus suscipit eleifend tellus, non interdum nunc fermentum congue. Sed ornare viverra tellus eget volutpat. "
		"In at neque vehicula, sollicitudin leo nec, dapibus quam. Donec dignissim euismod lorem vel varius. Donec vel enim purus. Nam sed pulvinar mi.", IVS_STATIC_TEXT, -0.8f, 0.8f, 1.0f);*/

	bool generate = false;
	UserInterface::button(generate, "Generate Terrrain");

	while (Display::isOpen()) {
		Controller::processInputs();

		Display::prepare();

		if (generate) {
			Terrain::generate();
			generate = false;
		}

		model->rotate(value, value, value);

		Render::render();

		Camera::update();

		Display::update();
	}

	Shaders::terminate();
	Display::terminate();
	return 0;
}