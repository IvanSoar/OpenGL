#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class uiElement {
protected:
	int x, y, width, height;
	uiElement* parent;
	glm::vec3 color;

	friend class Render;
	friend class Slider;
	friend class Button;

public:
	uiElement(int x, int y, int width, int height, glm::vec3 color, uiElement* parent) 
		: x(x), y(y), width(width), height(height), color(color), parent(parent) {}
};

class uiComponent {
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
	float step;

protected:
	Slider(int x, int y, int width, float& value, float min, float max, float step);
	
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

protected:
	Button(int x, int y, int width, int height, bool& value);

	void update() override;

	friend class UserInterface;
	friend class Render;
};

class UserInterface {
private:
	unsigned int VAO;
	std::vector<uiComponent*> componentList;
	std::vector<uiElement*> elementList;

private:
	UserInterface() {}

protected:
	static UserInterface& get();

	friend class Slider;

public:
	static void init();
	static void slider(int x, int y, int width, float& value, float min, float max, float step);
	static void button(int x, int y, int width, int height, bool& value);
	static void addElement(uiElement* element);
	static void addComponent(uiComponent* element);
	
	static std::vector<uiElement*> getElements();
	static std::vector<uiComponent*> getComponents();

	static unsigned int getVAO();
};
