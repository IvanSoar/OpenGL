#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Display
{
private:
	unsigned int screenWidth;
	unsigned int screenHeight;
	GLFWwindow* window;

private:
	static Display& get();
	void initImpl();
	Display() {}

public:
	static void init(unsigned int width, unsigned int height);
	static bool isOpen();
	static void terminate();
	static void prepare();
	static void update();
	static GLFWwindow* getWindow();
};