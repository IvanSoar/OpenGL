#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Display.h"
#include "Controller.h"
#include "../ivsEngine.h"

void aspectRatioCorrection(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Display& Display::get()
{
	static Display instance;
	return instance;
}

void Display::init()
{
	ivs::log("Initiating GLFW", glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	get().window = glfwCreateWindow(config::screenWidth, config::screenHeight, "OpenGL", NULL, NULL);
	ivs::log("Creating a window", !!get().window);
	glfwMakeContextCurrent(get().window);

	glfwSetFramebufferSizeCallback(get().window, aspectRatioCorrection);

	ivs::log("Initiating GLAD", gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glfwSwapInterval(config::vSync);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

bool Display::isOpen()
{
	return !glfwWindowShouldClose(get().window);
}

void Display::prepare()
{
	config::uiSecondaryColor = { config::uiColor.r * 0.3f, config::uiColor.g * 0.3f, config::uiColor.b * 0.3f, 1.0f };
	config::uiDetailColor = config::uiDetailColor = { config::uiColor.r * 0.6f, config::uiColor.g * 0.6f, config::uiColor.b * 0.6f, 1.0f };;
	glClearColor(config::clearColor.r, config::clearColor.g, config::clearColor.b, config::clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update()
{
	glfwSwapBuffers(get().window);
	glfwPollEvents();
}

GLFWwindow* Display::getWindow()
{
	return get().window;
}

void Display::terminate()
{
	glfwDestroyWindow(get().window);
	glfwTerminate();
}