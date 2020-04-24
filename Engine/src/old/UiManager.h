#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace UI {
	glm::vec4 MAIN_COLOR = { 1.0f, 0.0f, 0.0f, 0.05f };
	unsigned int PADDING = 10;
}

enum class ui_alignment {
	TOP, BOT, CENTER, LEFT, RIGHT, FREE
};

class uiContainer {
private:
	int x, y, width, height;
	bool visibility;

	ui_alignment horizontalAlignment;
	ui_alignment verticalAlignment;
};
	class basicContainer : uiContainer {
	};
	class window : uiContainer {
	};
	class hotbar : uiContainer {
	};

class uiComponent {
private:
	int x, y, width, height;
	bool visibility;
	
	uiContainer* parent;

	ui_alignment horizontalAlignment;
	ui_alignment verticalAlignment;

public:
	template <typename returnType>
	returnType evaluate();

	virtual void update();	
};
	class slider : uiComponent {
	};
	class button : uiComponent {
	};
	class checkbox : uiComponent {
	};

class uiElement {
private:
	int x, y, width, height;
	bool visibility;

	uiComponent* parent;

	ui_alignment verticalAlignment;
	ui_alignment horizontalAlignment;

public:
	bool isMouseOver();
	bool isButtonDown();
	bool isButtonUp();
	void isDragging();
};

class UiManager {
private:
	glm::vec4 uiColor;
	unsigned int padding;
	unsigned int uiVAO;

	std::vector<uiElement*> elementsList;

public:
	UiManager() : uiColor(UI::MAIN_COLOR), padding(UI::PADDING), uiVAO(init()) {}

	unsigned int init();
	std::vector<uiElement*> getElements();
	void addElement(uiElement* element);
};
