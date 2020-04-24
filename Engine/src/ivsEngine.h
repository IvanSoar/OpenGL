#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define IVS_LOG_STAMP "[ivsEngine] "
#define IVS_FAILURE ": failure!"
#define IVS_SUCCESS ": success!"

enum class render_mode : unsigned char
{
	ORTHO, PERSPECTIVE
};

#define IVS_ORTHO_MODE render_mode::ORTHO
#define IVS_PERSP_MODE render_mode::PERSPECTIVE

namespace ivs {
	template<typename type>
	void log(type msg, int value = 2) {
		switch (value) {
		case 0: std::cout << IVS_LOG_STAMP << msg << IVS_FAILURE << std::endl; break;
		case 1: std::cout << IVS_LOG_STAMP << msg << IVS_SUCCESS << std::endl; break;
		case 2: std::cout << IVS_LOG_STAMP << msg << std::endl; break;
		}
	}

	void wait();
};

namespace config {
	//field of view for perpective camera
	float fov;

	//how far the camera cam see
	float farPlane;

	//how close the camera can see
	float nearPlane;

	//how many unitys horizontaly on ortho
	int hOrthoFactor;

	//fix the framerate accordanly to monitor
	bool vSync;

	//back faces culled of
	bool cullFace;

	//test if the pixel is behide another one and does not render it if true
	bool dephtest;

	//size of the screen
	int screenWidth;
	int screenheight;

	//color to clear
	glm::vec3 clearColor;

	//current rendering mode
	render_mode renderMode;

	//duh!
	float cameraSpeed;

	//camera position int he x axis
	glm::vec3 cameraPos;

	//camera position int he z axis
	glm::vec3 cameraFront;

	//camera position int he y axis
	glm::vec3 cameraUp;
}