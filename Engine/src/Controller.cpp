#include "Display.h"
#include "../ivsEngine.h"
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
	get().scrollOffset = 0;
	glfwSetScrollCallback(Display::getWindow(), scroll_callback);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Controller::setScrollOffset(yoffset);
}

void Controller::processInputs()
{
	if (glfwGetKey(Display::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(Display::getWindow(), true);
	}

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_O) == GLFW_PRESS) {
		config::renderMode = false;
		config::cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
	}

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_P) == GLFW_PRESS) {
		config::renderMode = true;
		config::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	}

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_W) == GLFW_PRESS && config::renderMode == true)
		config::cameraPos += config::cameraSpeed * config::cameraFront;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_S) == GLFW_PRESS && config::renderMode == true)
		config::cameraPos -= config::cameraSpeed * config::cameraFront;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_W) == GLFW_PRESS && config::renderMode == false)
		config::cameraPos += config::cameraSpeed * config::cameraUp;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_S) == GLFW_PRESS && config::renderMode == false)
		config::cameraPos -= config::cameraSpeed * config::cameraUp;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		config::cameraPos -= glm::normalize(glm::cross(config::cameraFront, config::cameraUp)) * config::cameraSpeed;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		config::cameraPos += glm::normalize(glm::cross(config::cameraFront, config::cameraUp)) * config::cameraSpeed;

	if (glfwGetKey(Display::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		config::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		config::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		config::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}
}