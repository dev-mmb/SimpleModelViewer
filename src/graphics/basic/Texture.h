#pragma once
#include "glew.h"
#include <string>
#include <vector>

class Texture
{
public:
	Texture(std::string fileLoc, std::string type);

	void create(std::string fileLoc);
	bool load();
	void use();
	void clear();

	std::string getFileLocation() const { return fileLocation; }
	std::string getType() const { return type; }

	void setTextureWrapMode(GLuint mode) { this->textureWrapMode = mode; }
	void setTextureFilterMode(GLuint mode) { this->filterMode = mode; }
	void setTextureColorFormat(GLuint mode) { this->colorFormat = mode; }

	static void resetTextureIndex() { currentHighestTextureIndex = 0; }
	static void incrementTextureIndex() { currentHighestTextureIndex++; }

private:
	GLuint id;
	GLint textureWrapMode = GL_REPEAT, filterMode = GL_LINEAR, colorFormat = GL_RGBA;
	int width, height, bitDepth;
	std::string type;
	std::string fileLocation;
	static const std::vector<GLenum> textureIndexes;
	static int currentHighestTextureIndex;
};

