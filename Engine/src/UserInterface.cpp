#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "UserInterface.h"
#include "Display.h"
#include "Controller.h"
#include "../ivsEngine.h"

UserInterface& UserInterface::get()
{
	static UserInterface instance;
	return instance;
}

void UserInterface::init()
{
	float positions[] = { -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

	glGenVertexArrays(1, &get().VAO);
	glBindVertexArray(get().VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void UserInterface::slider(int x, int y, int width, float& value, float min, float max, float step)
{
	addComponent(new Slider(x, y, width, value, min, max, step));
}

void UserInterface::button(int x, int y, int width, int height, bool& value)
{
	addComponent(new Button(x, y, width, height, value));
}

void UserInterface::panel(ui_h_align halign, ui_v_align valign, float widthFactor, float heightFactor)
{
	addContainer(new Panel(halign, valign, widthFactor, heightFactor, true));
}

std::vector<uiElement*> UserInterface::getElements()
{
	return get().elementList;
}

std::vector<uiComponent*> UserInterface::getComponents()
{
	return get().componentList;
}

std::vector<uiContainer*> UserInterface::getContainers()
{
	return get().containerList;
}

unsigned int UserInterface::getVAO()
{
	return get().VAO;
}

void UserInterface::addElement(uiElement* element)
{
	get().elementList.emplace_back(element);
}

void UserInterface::addComponent(uiComponent* component)
{
	get().componentList.emplace_back(component);
}

void UserInterface::addContainer(uiContainer* container)
{
	get().containerList.emplace_back(container);
}

Slider::Slider(int x, int y, int width, float& value, float min, float max, float step)
	: x(x), y(y), width(width), value(&value), state(false), min(min), max(max), step(step)
{
	body = new uiElement(x + width / 2 + config::padding, y + width / 40 + config::padding, width, width / 20, config::uiColor, -config::layer1);

	head = new uiElement(body->x, body->y, body->height, body->height * 2, config::uiDetailColor, -config::layer2);

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
	body = new uiElement(x + width / 2 + config::padding, y + height / 2 + config::padding, width, height, config::uiColor, -config::layer1);

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

Panel::Panel(ui_h_align halign, ui_v_align valign, float widthFactor, float heightFactor, bool isVisible)
	: isVisible(isVisible), uiContainer(halign, valign, widthFactor, heightFactor)
{
	padding = config::padding;
	
	body = new uiElement(0, 0, 0, 0, config::uiSecondaryColor, -config::layer0);

	update();

	UserInterface::addElement(body);
}

void Panel::update()
{
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(Display::getWindow(), &screenWidth, &screenHeight);

	this->width = screenWidth * widthFactor;
	this->height = screenHeight * heightFactor;

	this->width -= widthFactor == 1.0f ? padding * 2 : 0;
	this->height -= heightFactor == 1.0f ? padding * 2 : 0;

	switch (halign) {
	case IVS_HALIGN_LEFT:
		x = this->width / 2 + padding;
		break;
	case IVS_HALIGN_CENTER: 
		x = screenWidth / 2;
		break;
	case IVS_HALIGN_RIGHT:
		x = screenWidth - this->width / 2 - padding;
		break;
	}

	switch (valign) {
	case IVS_VALIGN_TOP: 
		y = this->height / 2 + padding;
		break;
	case IVS_VALIGN_CENTER:
		y = screenHeight / 2;
		break;
	case IVS_VALIGN_BOTTOM:
		y = screenHeight - this->height / 2 - padding;
		break;
	}

	body->update(x, y, width, height, config::uiSecondaryColor);
}

void uiElement::update(int x, int y, int width, int height, glm::vec4 color)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}