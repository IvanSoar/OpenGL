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

	UserInterface::slider(config::maxVertexperTerrain, 1.0f, 1024.0f, 10.0f);
	UserInterface::slider(config::terrainSize, 1.0f, 1000.0f, 10.0f);

	bool generate = false;
	UserInterface::button(generate);

	Terrain::generate();
	
	Text::loadFont("CandaraASCII");
	Text::addText("O Ivan é lindo e gostoso!!", -0.5f, 0);

	UserInterface::panel(IVS_HALIGN_RIGHT);
	UserInterface::slider(config::textColor.r, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::textColor.g, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::textColor.b, 0.0f, 1.0f, 0.1f);
	UserInterface::slider(config::textWidth, 0.3f, 0.5f, 0.1f);
	UserInterface::slider(config::textEdge, 0.3f, 0.01f, 0.1f);

	std::string nome = "Ivan ";
	std::string sobrenome = "Ivan ";

	ivs::log(nome + sobrenome);

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