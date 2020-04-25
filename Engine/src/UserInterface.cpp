#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "UserInterface.h"
#include "Display.h"
#include "Controller.h"
#include "ivsEngine.h"

UserInterface& UserInterface::get()
{
	static UserInterface instance;

	float positions[] = { -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

	glGenVertexArrays(1, &instance.VAO);
	glBindVertexArray(instance.VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return instance;
}

void UserInterface::slider(int x, int y, int width, float& value, float min, float max, float step)
{
	Slider* slider = new Slider(x, y, width, value, min, max, step);
	addComponent(slider);
}

void UserInterface::button(int x, int y, int width, int height, bool& value)
{
	Button* button = new Button(x, y, width, height, value);
	addComponent(button);
}

std::vector<uiElement*> UserInterface::getElements()
{
	return get().elementList;
}

std::vector<uiComponent*> UserInterface::getComponents()
{
	return get().componentList;
}

unsigned int UserInterface::getVAO()
{
	return get().VAO;
}

void UserInterface::addComponent(uiComponent* component)
{
	get().componentList.emplace_back(component);
}

void UserInterface::addElement(uiElement* element)
{
	get().elementList.emplace_back(element);
}

Slider::Slider(int x, int y, int width, float& value, float min, float max, float step)
	: x(x), y(y), width(width), value(&value), state(false), min(min), max(max), step(step)
{
	body = new uiElement(x + width / 2 + config::padding, y + width / 40 + config::padding, width, width / 20, config::uiColor, nullptr);
	head = new uiElement(body->x, body->y, body->height, body->height * 2, body->color * 0.5f, body);

	UserInterface::addElement(head);
	UserInterface::addElement(body);
}

void Slider::update()
{
	if (Controller::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		if (Controller::isMouseOver(head->x, head->y, head->width, head->height) ||
			Controller::isMouseOver(body->x, body->y, body->width, body->height)) {
			state = true;
		}
	}
	else {
		state = false;
	}

	if (Controller::isMouseOver(head->x, head->y, head->width, head->height) ||
		Controller::isMouseOver(body->x, body->y, body->width, body->height)) {
		head->x += Controller::scrollUp();
		head->x -= Controller::scrollDown();
	}

	double mouseX;
	glfwGetCursorPos(Display::getWindow(), &mouseX, nullptr);

	if (state)
		head->x = (int)mouseX;

	head->x = head->x > body->x + body->width / 2 ? body->x + body->width / 2 : head->x;
	head->x = head->x < body->x - body->width / 2 ? body->x - body->width / 2 : head->x;

	*value = ivs::map((float)body->x - body->width / 2, (float)body->x + body->width / 2, (float)min, (float)max, (float)head->x);
}

Button::Button(int x, int y, int width, int height, bool& value)
	: x(x), y(y), width(width), height(height), value(&value)
{
	body = new uiElement(x + width / 2 + config::padding, y + height / 2 + config::padding, width, height, config::uiColor, nullptr);

	UserInterface::addElement(body);
}

void Button::update()
{
	if (Controller::isButtonDown(GLFW_MOUSE_BUTTON_LEFT) && Controller::isMouseOver(body->x, body->y, body->width, body->height) && state == 0)
	{
		ivs::log("clicked");
		*value = *value ? false : true;
		ivs::log(*value);
		state++;

		body->x += 2;
		body->y += 2;
		body->width -= 2;
		body->height -= 2;
		body->color *= 0.5f;
	}
	if (!Controller::isButtonDown(GLFW_MOUSE_BUTTON_LEFT) && state != 0) {
		state = 0;
		body->x -= 2;
		body->y -= 2;
		body->width += 2;
		body->height += 2;
		body->color /= 0.5f;
	}
}
