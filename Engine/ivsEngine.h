#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define IVS_LOG_STAMP "[ivsEngine] "
#define IVS_FAILURE ": failure!"
#define IVS_SUCCESS ": success!"

enum class ui_h_align : unsigned char
{
	LEFT, CENTER, RIGHT
};

enum class ui_v_align : unsigned char
{
	TOP, CENTER, BOTTOM
};

#define IVS_HALIGN_LEFT ui_h_align::LEFT
#define IVS_HALIGN_CENTER ui_h_align::CENTER
#define IVS_HALIGN_RIGHT ui_h_align::RIGHT
#define IVS_VALIGN_TOP ui_v_align::TOP
#define IVS_VALIGN_CENTER ui_v_align::CENTER
#define IVS_VALIGN_BOTTOM ui_v_align::BOTTOM

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
	inline static	float		nearPlaneO = 0.0f;
	inline static	float		farPlaneO = 0.04f;
	inline static	float		nearPlaneP = 0.05f;
	inline static	float		farPlaneP = 100.0f;
	inline static	int			hOrthoFactor = 10;
	inline static	bool		vSync = true;
	inline static	int			screenWidth = 1600;
	inline static	int			screenHeight = 900;
	inline static	glm::vec4	clearColor = { 0.2f, 0.8f, 0.3f, 1.0f };
	inline static	bool		renderMode = true;
	inline static	float		cameraSpeed = 1.0f;
	inline static	glm::vec3	cameraPos = { 0.0f, 1.0f, 3.0f };
	inline static	glm::vec3	cameraFront = { 0.0f, 0.0f, -1.0f };
	inline static	glm::vec3	cameraUp = { 0.0f, 1.0f, 0.0f };
	inline static	glm::vec4	uiColor = { 0.4f, 0.4f, 0.8f, 1.0f };
	inline static	glm::vec4	uiSecondaryColor = { uiColor.r * 0.3f, uiColor.g * 0.3f, uiColor.b * 0.3f, 1.0f };
	inline static	glm::vec4	uiDetailColor = { uiColor.r * 0.6f, uiColor.g * 0.6f, uiColor.b * 0.6f, 1.0f };
	inline static	int			padding = 10;
	inline static	float		maxVertexperTerrain = 10;
	inline static	float		terrainSize  = 10;
	inline static	float		uiWidthFactor = 0.2f;
	inline static	float		uiHeightFactor = 1.0f;
	inline static	float		layer0 = 0.03f;
	inline static	float		layer1 = 0.02f;
	inline static	float		layer2 = 0.01f;
	inline static	float		textWidth = 0.5f;
	inline static	float		textEdge = 0.1f;
	inline static	glm::vec3	textColor = { 0.0f, 0.0f, 0.0f };
};