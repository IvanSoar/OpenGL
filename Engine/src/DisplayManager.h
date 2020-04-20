#pragma once

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraManager.h"
#include "RendererManager.h"
#include "Utils.h"

class DisplayManager {
protected:
	const unsigned int screenWidth = 800;
	const unsigned int screenHeight = 600;

	float ASPECT_RATIO = (float)screenWidth / (float)screenHeight;

	float FOV = 45.0f;
	float FOVCorrection = 0.0f;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 100.0f;
	display_mode MODE;

	friend class RendererManager;

public:
	GLFWwindow* window;
	glm::vec4 clearColor;
	unsigned int swapInterval = 0;

public:
	DisplayManager();
	void config();
	bool isOpen() const;
	void processInputs(CameraManager* cam, RendererManager* render);
	void prepare() const;
	void update() const;
	void destroy() const;

	void setClearColor(float* color);
	void activateVSync(bool value);
};