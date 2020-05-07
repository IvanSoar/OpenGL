#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image/stb_image.h"

#include <fstream>
#include <string>

#include "Text.h"
#include "Display.h"
#include "Shaders.h"
#include "../ivsEngine.h"

void Text::updateIndex()
{
	indices.clear();
	for (unsigned int iterator = 0; iterator < textString.size(); iterator++) {
		indices.push_back(iterator * 4 + 0);
		indices.push_back(iterator * 4 + 1);
		indices.push_back(iterator * 4 + 2);

		indices.push_back(iterator * 4 + 2);
		indices.push_back(iterator * 4 + 3);
		indices.push_back(iterator * 4 + 0);
	}
}

void Text::updateVertex()
{
	vertices.clear();

	float cursorX = x;
	float cursorY = y;
	float size = 0;

	bool flag = false;
	for (auto character : textString) {
		float charWidth = (float)TextHandler::characters[character].width / (float)TextHandler::textureWidth;
		float charHeight = (float)TextHandler::characters[character].height / (float)TextHandler::textureHeight;

		float x1 = (float)TextHandler::characters[character].x / (float)TextHandler::textureWidth;
		float x2 = x1 + charWidth;

		float y1 = 1 - (float)TextHandler::characters[character].y / (float)TextHandler::textureHeight;
		float y2 = y1 - charHeight;

		float xoffset = (float)TextHandler::characters[character].xoffset / (float)TextHandler::textureWidth;
		float yoffset = (float)TextHandler::characters[character].yoffset / (float)TextHandler::textureHeight;

		vertices.push_back(cursorX);
		vertices.push_back(cursorY - yoffset);
		vertices.push_back(x1);
		vertices.push_back(y1);

		vertices.push_back(cursorX);
		vertices.push_back(cursorY - charHeight - yoffset);
		vertices.push_back(x1);
		vertices.push_back(y2);

		vertices.push_back((cursorX + charWidth));
		vertices.push_back(cursorY - charHeight - yoffset);
		vertices.push_back(x2);
		vertices.push_back(y2);

		vertices.push_back((cursorX + charWidth));
		vertices.push_back(cursorY - yoffset);
		vertices.push_back(x2);
		vertices.push_back(y1);

		size += ((float)TextHandler::characters[character].xadvance / (float)TextHandler::textureWidth) + xoffset;
		flag = size >= lineWidth ? true : flag;

		cursorX += ((float)TextHandler::characters[character].xadvance / (float)TextHandler::textureWidth) + xoffset;
		if (flag && character == ' ') {
			cursorX = x;
			cursorY -= 0.1f;
			flag = false;
			size = 0;
		}
	}
}

void Text::createVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, sizeof(vertex::positions) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, positions));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, sizeof(vertex::textureCoords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords));
	glEnableVertexAttribArray(1);
}

void Text::updateDynamicData()
{
	updateIndex();
	updateVertex();

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
}

void Text::createDynamicVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, config::maxQuads * 4 * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, config::maxQuads * 6 * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, sizeof(vertex::positions) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, positions));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, sizeof(vertex::textureCoords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords));
	glEnableVertexAttribArray(1);
}


std::string& TextHandler::getText(unsigned int textId)
{
	return texts[textId]->textString;
}


void TextHandler::loadTexture(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(1);
	textureBuffer = stbi_load(filepath.c_str(), &textureWidth, &textureHeight, &textureBPP, 4);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TextHandler::loadFontFile(const std::string& filepath)
{
	std::ifstream file(filepath, std::ifstream::in);
	std::string line;

	int id, x, y, width, height, xoffset, yoffset, xadvance;
	while (!file.eof()) {
		getline(file, line);
		if (line.find("char id=") != std::string::npos) {
			id = stoi(line.substr(8, line.find(' ')));
			x = stoi(line.substr(line.find("x=") + 2, line.find(' ')));
			y = stoi(line.substr(line.find("y=") + 2, line.find(' ')));
			width = stoi(line.substr(line.find("width=") + 6, line.find(' ')));
			height = stoi(line.substr(line.find("height=") + 7, line.find(' ')));
			xoffset = stoi(line.substr(line.find("xoffset=") + 8, line.find(' ')));
			yoffset = stoi(line.substr(line.find("yoffset=") + 8, line.find(' ')));
			xadvance = stoi(line.substr(line.find("xadvance=") + 9, line.find(' ')));

			characters[id] = { x, y, width, height, xoffset, yoffset, xadvance };
		}
	}
	file.close();
}

void TextHandler::loadFont(const std::string& fontName)
{
	loadTexture("res/fonts/" + fontName + ".png");
	loadFontFile("res/fonts/" + fontName + ".fnt");
}

unsigned int TextHandler::text(const std::string& text, text_rendering_type textType, float x, float y, float lineWidth)
{
	Text* instance = new Text(text, textType, x, y + texts.size() * 0.1f, lineWidth);

	if (textType == IVS_DYNAMIC_TEXT) {
		instance->createDynamicVAO();
		instance->updateDynamicData();
	}
	else {
		instance->updateIndex();
		instance->updateVertex();
		instance->createVAO();
	}

	unsigned int id = texts.size();
	texts[id] = instance;
	return id;
}
