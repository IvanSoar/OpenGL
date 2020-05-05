#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image/stb_image.h"

#include <fstream>
#include <string>

#include "Text.h"
#include "Display.h"
#include "Shaders.h"
#include "../ivsEngine.h"

Text& Text::get()
{
	static Text instance;
	return instance;
}

void Text::loadFont(const std::string& fontName)
{
	loadTexture("res/fonts/" + fontName + ".png");
	loadFontFile("res/fonts/" + fontName + ".fnt");

	Shaders::activate(3);
	Shaders::setUniform1i(glGetUniformLocation(Shaders::getShaders()[3], "u_Texture"), 0);
}

void Text::createVAO()
{
	auto& instance = get();

	glGenVertexArrays(1, &instance.vao);
	glBindVertexArray(instance.vao);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, instance.vertex.size() * sizeof(float), instance.vertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, instance.index.size() * sizeof(unsigned int), instance.index.data(), GL_STATIC_DRAW);
}

void Text::render()
{
	Shaders::activate(3);
	Shaders::setUniform3f(glGetUniformLocation(Shaders::getShaders()[3], "textColor"), config::textColor);
	Shaders::setUniform1f(glGetUniformLocation(Shaders::getShaders()[3], "width"), config::textWidth);
	Shaders::setUniform1f(glGetUniformLocation(Shaders::getShaders()[3], "edge"), config::textEdge);

	glBindVertexArray(get().vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, get().textureID);

	glDrawElements(GL_TRIANGLES, get().index.size(), GL_UNSIGNED_INT, 0);

}

void Text::loadTexture(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(1);
	get().textureBuffer = stbi_load(filepath.c_str(), &get().textureWidth, &get().textureHeight, &get().textureBPP, 4);

	glGenTextures(1, &get().textureID);
	glBindTexture(GL_TEXTURE_2D, get().textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, get().textureWidth, get().textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, get().textureBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text::loadFontFile(const std::string& filepath)
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

			get().characters[id] = new CharacterData(x, y, width, height, xoffset, yoffset, xadvance);
		}
	}
	file.close();
}

void Text::addText(const std::string& text, float x, float y)
{
	float cursorX = x;
	float cursorY = y;
	auto& vertex = get().vertex;
	auto& index = get().index;

	int scrWidth, scrHeight;
	glfwGetFramebufferSize(Display::getWindow(), &scrWidth, &scrHeight);
	float aspectRatio = (float) scrWidth / (float) scrHeight;

	int iterator = 0;
	for (auto character : text) {
		float charWidth = get().characters[character]->width / (float)get().textureWidth;
		float charHeight = get().characters[character]->height / (float)get().textureHeight;

		float x1 = (float)get().characters[character]->x / (float)get().textureWidth;
		float x2 = x1 + charWidth;

		float y1 = 1 - (float)get().characters[character]->y / (float)get().textureHeight;
		float y2 = y1 - charHeight;

		float xoffset = (float)get().characters[character]->xoffset / (float)get().textureWidth;
		float yoffset = (float)get().characters[character]->yoffset / (float)get().textureHeight;

		vertex.push_back(cursorX / aspectRatio);
		vertex.push_back(cursorY - yoffset);
		vertex.push_back(x1);
		vertex.push_back(y1);

		vertex.push_back(cursorX / aspectRatio);
		vertex.push_back(cursorY - charHeight - yoffset);
		vertex.push_back(x1);
		vertex.push_back(y2);

		vertex.push_back((cursorX + charWidth) / aspectRatio);
		vertex.push_back(cursorY - charHeight - yoffset);
		vertex.push_back(x2);
		vertex.push_back(y2);

		vertex.push_back((cursorX + charWidth) / aspectRatio);
		vertex.push_back(cursorY - yoffset);
		vertex.push_back(x2);
		vertex.push_back(y1);

		index.push_back(iterator * 4 + 0);
		index.push_back(iterator * 4 + 1);
		index.push_back(iterator * 4 + 2);

		index.push_back(iterator * 4 + 2);
		index.push_back(iterator * 4 + 3);
		index.push_back(iterator * 4 + 0);

		cursorX += (float)get().characters[character]->xadvance / (float)get().textureWidth + xoffset;
		iterator++;
	}

	createVAO();
}
