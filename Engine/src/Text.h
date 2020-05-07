#pragma once

#include <string>
#include <map>
#include <vector>

struct vertex {
	float positions[2];
	float textureCoords[2];
};

struct CharacterData {
	int x, y, width, height, xoffset, yoffset, xadvance;
};

class Text {
protected:
	float x, y, lineWidth;
	std::string textString;

	unsigned int vao;
	unsigned int ebo;
	unsigned int vbo;

	std::vector<unsigned int> indices;
	std::vector<float> vertices;

	void updateIndex();
	void updateVertex();
	void createVAO();

	void createDynamicVAO();
	void updateDynamicData();

	friend class TextHandler;
	friend class Render;

public:
	Text(const std::string& string, float x, float y, float lineWidth) : textString(string), x(x), y(y), lineWidth(lineWidth), vao(0), vbo(0), ebo(0) {}


};

class TextHandler {
protected:
	inline static unsigned int textureID;
	inline static unsigned char* textureBuffer;
	inline static int textureWidth, textureHeight, textureBPP;

	inline static std::map<unsigned char, CharacterData> characters;
	inline static std::map<unsigned int, Text*> texts;

	friend class Text;
	friend class Render;

public:
	static void loadTexture(const std::string& filepath);
	static void loadFontFile(const std::string& filepath);
	static void loadFont(const std::string& fontName);
	static unsigned int add(const std::string& text, float x, float y, float lineWidth);
	static std::string& getText(unsigned int textId);
};