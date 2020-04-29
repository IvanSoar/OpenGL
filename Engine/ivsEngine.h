#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define IVS_LOG_STAMP "[ivsEngine] "
#define IVS_FAILURE ": failure!"
#define IVS_SUCCESS ": success!"

namespace ivs {
	template<typename type>
	void log(type msg, int value = 2)
	{
		switch (value) {
		case 0: std::cout << IVS_LOG_STAMP << msg << IVS_FAILURE << std::endl; break;
		case 1: std::cout << IVS_LOG_STAMP << msg << IVS_SUCCESS << std::endl; break;
		case 2: std::cout << IVS_LOG_STAMP << msg << std::endl; break;
		}
	}

	template<typename type>
	inline type map(type input_start, type input_end, type output_start, type output_end, type input) {
		return (input - input_start) / (input_end - input_start) * (output_end - output_start) + output_start;
	}

	inline void wait()
	{
		std::cin.get();
	}
};

class config {
public:
	inline static	float		fov = 55.0f;
	inline static	float		nearPlaneP = 0.1f;
	inline static	float		farPlaneP = 1000.0f;
	inline static	float		nearPlaneO = 0.1f;
	inline static	float		farPlaneO = 0.2f;
	inline static	int			hOrthoFactor = 10;
	inline static	bool		vSync = true;
	inline static	bool		cullFace = true;
	inline static	bool		dephtest = true;
	inline static	int			screenWidth = 1000;
	inline static	int			screenHeight = 500;
	inline static	glm::vec4	clearColor = { 0.2f, 0.8f, 0.3f, 1.0f };
	inline static	bool		renderMode = true;
	inline static	float		cameraSpeed = 1.0f;
	inline static	glm::vec3	cameraPos = { 0.0f, 1.0f, 3.0f };
	inline static	glm::vec3	cameraFront = { 0.0f, 0.0f, -1.0f };
	inline static	glm::vec3	cameraUp = { 0.0f, 1.0f, 0.0f };
	inline static	glm::vec4	uiColor = { 1.0f, 0.5f, 0.0f, 1.0f };
	inline static	int			padding = 10;
	inline static	int			maxVertexperTerrain = 10;
	inline static	int			terrainSize  = 10;
};