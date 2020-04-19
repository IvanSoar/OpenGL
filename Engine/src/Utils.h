#pragma once

#include <string>

#define NIKKO_LOG_STAMP "[NIKKO LOG]: "
#define NIKKO_FAILURE ": failure!"
#define NIKKO_SUCCESS ": success!"
#define NIKKO_BACKGROUND_RGBA_COLOR 0.2f, 0.3f, 0.3f, 1.0f

enum class model_t : unsigned char {
	GUI, NOTGUI
};

#define NK_GUI model_t::GUI
#define NK_NOTGUI model_t::NOTGUI

enum class display_mode : unsigned char {
	ORTHO, PERSPECTIVE
};

#define NK_ORTHO display_mode::ORTHO
#define NK_PERSPECTIVE display_mode::PERSPECTIVE

enum class gui_window_align : unsigned char {
	TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER, TOP_CENTER, BOTTOM_CENTER, LEFT_CENTER, RIGHT_CENTER
};

#define NK_TOPL gui_window_align::TOP_LEFT
#define NK_TOPC gui_window_align::TOP_CENTER
#define NK_TOPR gui_window_align::TOP_RIGHT
#define NK_BOTL gui_window_align::BOTTOM_LEFT
#define NK_BOTC gui_window_align::BOTTOM_CENTER
#define NK_BOTR gui_window_align::BOTTOM_RIGHT
#define NK_RIGC gui_window_align::RIGHT_CENTER
#define NK_LEFC gui_window_align::LEFT_CENTER
#define NK_CENTER gui_window_align::CENTER

enum class game_state : unsigned char {
	MENU, GAME
};

#define NK_MENU game_state::MENU
#define NK_GAME game_state::GAME

namespace nk
{
	struct grid {
		float* vertices;
		int* indices;
		int verticesCount;
	};

	void Log(const std::string& msg, int type = 2);
}