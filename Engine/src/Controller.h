#pragma once

#include "GLFW/glfw3.h"

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Controller {
private:
	double scrollOffset;

private:
	Controller() {}

public:
	static Controller& get();
	static bool isMouseOver(int x, int y, int width, int height);
	static bool isButtonDown(int mouseButton);
	static bool scrollUp();
	static bool scrollDown();
	static void setScrollOffset(double offset);
	static void init();

	void initImpl();
};