#pragma once

#include <string>
#include <map>
#include <vector>

class CharacterData {
public:
	int x, y, width, height, xoffset, yoffset, xadvance;
	
	CharacterData(int x, int y, int width, int height, int xoffset, int yoffset, int xadvance)
		: x(x), y(y), width(width), height(height), xoffset(xoffset), yoffset(yoffset), xadvance(xadvance) {}
};

class Text {
private:
	unsigned int vao;
	int x, y, width, height;
	std::map<char, CharacterData*> characters;
	std::vector<float> vertex;
	std::vector<unsigned int> index;

	unsigned int textureID;
	unsigned char* textureBuffer;
	int textureWidth, textureHeight, textureBPP;

	static Text& get();
	Text() {}
	Text(const Text&) = delete;

public:
	static void loadFont(const std::string& fontName);
	static void createVAO();
	static void render();
	static void loadTexture(const std::string& filepath);
	static void loadFontFile(const std::string& filepath);
	static void addText(const std::string& text, float x, float y);
};