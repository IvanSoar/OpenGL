#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../ivsEngine.h"

class uiElement {
public:
	int x, y, width, height;
	float zLayer;
	glm::vec4 color;

	friend class Render;
	friend class Slider;
	friend class Button;

public:
	uiElement(int x, int y, int width, int height, glm::vec4 color, float zLayer) 
		: x(x), y(y), width(width), height(height), color(color), zLayer(zLayer) {}

	void update(int x, int y, int width, int height, glm::vec4 color);
};

class uiComponent {
public:
	virtual void update() = 0;
};

class uiContainer {
public:
	ui_h_align halign;
	ui_v_align valign;
	float widthFactor;
	float heightFactor;
	int componenteCount = 0;
	
	int x = 0, y = 0;
	unsigned int width = 0, height = 0;
	int padding = 0;

	uiContainer(ui_h_align halign, ui_v_align valign, float widthFactor, float heightFactor)
		: halign(halign), valign(valign), widthFactor(widthFactor), heightFactor(heightFactor) {}

public:
	virtual void update() = 0;
};

class Slider : uiComponent {
private:
	int x, y, width;
	bool state;
	uiElement* head;
	uiElement* body;
	float* value;
	float min, max;
	float precision;
	uiContainer& container;
	unsigned int text;

protected:
	Slider(int x, int y, int width, float& value, float min, float max, float precision, uiContainer& container);
	
	void update() override;
	
	friend class UserInterface;
	friend class Render;
};

class Button : uiComponent {
private:
	int x, y, width, height;
	uiElement* body;
	bool* value;
	int state = 0;
	uiContainer& container;

protected:
	Button(int x, int y, int width, int height, bool& value, const std::string& label, uiContainer& container);

	void update() override;

	friend class UserInterface;
	friend class Render;
};

class Panel : public uiContainer {
private:
	uiElement* body;
	bool isVisible;

protected:
	Panel(ui_h_align halign, ui_v_align valign, float widthFactor, float heightFactor, bool isVisible);

	void update() override;

	friend class UserInterface;
	friend class Render;
};

class UserInterface {
private:
	unsigned int VAO;
	std::vector<uiContainer*> containerList;
	std::vector<uiComponent*> componentList;
	std::vector<uiElement*> elementList;

private:
	UserInterface() {}

protected:
	static UserInterface& get();

	friend class Slider;

public:
	static void init();
	static void slider(float& value, float min, float max, float precision);
	static void button(bool& value, const std::string& label);
	static void panel(ui_h_align halign, ui_v_align valign = IVS_VALIGN_CENTER, float widthFactor = config::uiWidthFactor, float heightFactor = config::uiHeightFactor);

	static void addElement(uiElement* element);
	static void addComponent(uiComponent* component);
	static void addContainer(uiContainer* container);
	
	static std::vector<uiElement*> getElements();
	static std::vector<uiComponent*> getComponents();
	static std::vector<uiContainer*> getContainers();

	static unsigned int getVAO();
};