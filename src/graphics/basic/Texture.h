#pragma once
#include "glew.h"
#include <string>
class Texture
{
public:
	Texture(std::string fileLoc);

	bool load();
	void use();
	void clear();

	void setTextureWrapMode(GLuint mode) { this->textureWrapMode = mode; }
	void setTextureFilterMode(GLuint mode) { this->filterMode = mode; }
	void setTextureColorFormat(GLuint mode) { this->colorFormat = mode; }
private:
	GLuint id;
	GLint textureWrapMode = GL_REPEAT, filterMode = GL_LINEAR, colorFormat = GL_RGBA;
	int width, height, bitDepth;
	std::string fileLocation;
};

