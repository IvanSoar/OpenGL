#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Display
{
private:
	GLFWwindow* window;
private:
	static Display& get();
	Display() {}

public:
	static void init();
	static bool isOpen();
	static void terminate();
	static void prepare();
	static void update();
	static GLFWwindow* getWindow();
};