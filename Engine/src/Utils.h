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

enum class gui_element_align : unsigned char {
	FREE, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER, TOP_CENTER, BOTTOM_CENTER, LEFT_CENTER, RIGHT_CENTER
};

#define NK_GUI_TOPL gui_element_align::TOP_LEFT
#define NK_GUI_TOPC gui_element_align::TOP_CENTER
#define NK_GUI_TOPR gui_element_align::TOP_RIGHT
#define NK_GUI_BOTL gui_element_align::BOTTOM_LEFT
#define NK_GUI_BOTC gui_element_align::BOTTOM_CENTER
#define NK_GUI_BOTR gui_element_align::BOTTOM_RIGHT
#define NK_GUI_RIGC gui_element_align::RIGHT_CENTER
#define NK_GUI_LEFC gui_element_align::LEFT_CENTER
#define NK_GUI_CENTER gui_element_align::CENTER
#define NK_GUI_FREE gui_element_align::FREE

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