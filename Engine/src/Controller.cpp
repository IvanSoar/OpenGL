#include "Display.h"
#include "ivsEngine.h"
#include "Controller.h"

Controller& Controller::get()
{
	static Controller instance;
	return instance;
}

bool Controller::isMouseOver(int x, int y, int width, int height) {
	double xpos, ypos;
	glfwGetCursorPos(Display::getWindow(), &xpos, &ypos);
	if ((xpos > x - width / 2 && xpos < x + width / 2) && (ypos > y - height / 2 && ypos < y + height / 2))
		return 1;
	return 0;
}

bool Controller::isButtonDown(int mouseButton)
{
	return glfwGetMouseButton(Display::getWindow(), mouseButton) && GLFW_PRESS;
}

bool Controller::scrollUp()
{
	if (get().scrollOffset > 0.0f) {
		get().scrollOffset = 0.0f;
		return true;
	}
	return false;
}

bool Controller::scrollDown()
{
	if (get().scrollOffset < 0.0f) {
		get().scrollOffset = 0.0f;
		return true;
	}
	return false;
}

void Controller::setScrollOffset(double offset)
{
	get().scrollOffset = offset;
}

void Controller::init()
{
	get().initImpl();
}

void Controller::initImpl()
{
	get().scrollOffset = 0;
	glfwSetScrollCallback(Display::getWindow(), scroll_callback);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Controller::setScrollOffset(yoffset);
}
