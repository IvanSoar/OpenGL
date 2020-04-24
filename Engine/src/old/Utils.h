#pragma once

#include <string>

#define NIKKO_LOG_STAMP "[NIKKO LOG]: "
#define NIKKO_FAILURE ": failure!"
#define NIKKO_SUCCESS ": success!"
#define NIKKO_BACKGROUND_RGBA_COLOR 0.2f, 0.3f, 0.3f, 1.0f

enum class display_mode : unsigned char {
	ORTHO, PERSPECTIVE
};

#define NK_ORTHO display_mode::ORTHO
#define NK_PERSPECTIVE display_mode::PERSPECTIVE

enum class game_state : unsigned char {
	MENU, GAME
};

#define NK_MENU game_state::MENU
#define NK_GAME game_state::GAME

enum class gui_element_type : unsigned char {
	OTHER, WINDOW, CLOSE_WINDOW_BUTTON, SLIDER_HEAD, SLIDER_BODY
};

#define OTHER gui_element_type::OTHER
#define WINDOW gui_element_type::WINDOW
#define CLOSE_BUTTON gui_element_type::CLOSE_WINDOW_BUTTON
#define SLIDER_HEAD gui_element_type::SLIDER_HEAD
#define SLIDER_BODY gui_element_type::SLIDER_BODY

namespace nk
{
	struct grid {
		float* vertices;
		int* indices;
		int verticesCount;
	};

	void Log(const std::string& msg, int type = 2);

	int mapInt(int input_start, int input_end, int output_start, int output_end, int input);
}