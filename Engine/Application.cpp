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

	UserInterface::panel(IVS_HALIGN_LEFT);

	UserInterface::slider(config::clearColor.r, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::clearColor.g, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::clearColor.b, 0.0f, 1.0f, 0.1f);

	UserInterface::slider(config::uiColor.r, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::uiColor.g, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::uiColor.b, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::uiSecondaryColor.a, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::cameraSpeed, 0.1f, 3.0f, 0.1f);

	float value = 0.0f;
	UserInterface::slider(value, -0.3f, 0.3f, 0.1f);

	/*UserInterface::slider(config::maxVertexperTerrain, 1.0f, 1024.0f, 10.0f);
	UserInterface::slider(config::terrainSize, 1.0f, 1000.0f, 10.0f);*/

	bool generate = false;
	UserInterface::button(generate);

	Terrain::generate();
	
	TextHandler::loadFont("CandaraASCII");
	auto sliderText = TextHandler::text("ivan", IVS_DYNAMIC_TEXT);


	/*TextHandler::add("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce id massa vitae nunc ultrices sodales. "
		"Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Cras ultricies varius dui, scelerisque posuere elit iaculis a. "
		"Fusce sed semper nulla, quis finibus nunc. Vivamus suscipit eleifend tellus, non interdum nunc fermentum congue. Sed ornare viverra tellus eget volutpat. "
		"In at neque vehicula, sollicitudin leo nec, dapibus quam. Donec dignissim euismod lorem vel varius. Donec vel enim purus. Nam sed pulvinar mi.", -0.8f, 0.8f, 1.0f);*/


	UserInterface::panel(IVS_HALIGN_RIGHT);

	float sliderValue = 0;
	float precision = 0;
	UserInterface::slider(sliderValue, 0, 100, 1);
	UserInterface::slider(precision, 1, 6, 1);

	while (Display::isOpen()) {
		Controller::processInputs();

		Display::prepare();

		if (generate) {
			Terrain::generate();
			generate = false;
		}

		model->rotate(value, value, value);


		precision = (int)precision == 1.0f ? 0.0f : precision;
		TextHandler::getText(sliderText).assign(std::to_string(sliderValue).substr(0, std::to_string(sliderValue).find('.') + precision));

		Render::render();

		Camera::update();

		Display::update();
	}

	Shaders::terminate();
	Display::terminate();
	return 0;
}