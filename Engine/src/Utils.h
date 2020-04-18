#pragma once

#include <string>

#define NIKKO_LOG_STAMP "[NIKKO LOG]: "
#define NIKKO_FAILURE ": failure!"
#define NIKKO_SUCCESS ": success!"
#define NIKKO_BACKGROUND_RGBA_COLOR 0.2f, 0.3f, 0.3f, 1.0f

namespace nk
{
	struct grid {
		float* vertices;
		int* indices;
		int verticesCount;
	};

	void Log(const std::string& msg, int type = 2);
}