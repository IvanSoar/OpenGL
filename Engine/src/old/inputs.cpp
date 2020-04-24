void DisplayManager::processInputs(CameraManager* camera, RendererManager* renderer)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		FOV += FOV == 180 ? 0.0f : 1.0f;
		std::cout << "FOV: " << FOV << std::endl;
	}
	
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		FOV -= FOV == 0 ? 0.0f : 1.0f;
		std::cout << "FOV: " << FOV << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		MODE = NK_ORTHO;
		std::cout << "DISPLAY MODE CHANGED: " << "ORTHOGONAL" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		MODE = NK_PERSPECTIVE;
		camera->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		std::cout << "DISPLAY MODE CHANGED: " << "PERSPECTIVE" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && MODE == NK_PERSPECTIVE)
		camera->cameraPos += camera->cameraSpeed * camera->cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && MODE == NK_PERSPECTIVE)
		camera->cameraPos -= camera->cameraSpeed * camera->cameraFront;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && MODE == NK_ORTHO)
		camera->cameraPos += camera->cameraSpeed * camera->cameraUp;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && MODE == NK_ORTHO)
		camera->cameraPos -= camera->cameraSpeed * camera->cameraUp;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * camera->cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * camera->cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		camera->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		camera->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}
}