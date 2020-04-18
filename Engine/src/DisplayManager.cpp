#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "DisplayManager.h"
#include "RendererManager.h"

void aspectRatioCorrection(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

DisplayManager::DisplayManager() : clearColor(NIKKO_BACKGROUND_RGBA_COLOR)
{
	nk::Log("GLFW init", glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);
	nk::Log("Window create", !!window);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, aspectRatioCorrection);

	nk::Log("glad init", gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	config();
}

void DisplayManager::prepare() const
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DisplayManager::update() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool DisplayManager::isOpen() const
{
	return !glfwWindowShouldClose(window);
}

void DisplayManager::processInputs()
{
}

void DisplayManager::destroy() const
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void DisplayManager::setClearColor(float* color)
{
	clearColor = glm::vec4(color[0], color[1], color[2], color[3]);
}

void DisplayManager::activateVSync(bool value)
{
	glfwSwapInterval(value);
}

void DisplayManager::config()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}