#include "Texture.h"

#include <utility>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
int Texture::currentHighestTextureIndex = 0;
const std::vector<GLenum> Texture::textureIndexes = std::vector<GLenum>{
	GL_TEXTURE0,
	GL_TEXTURE1,
	GL_TEXTURE2,
	GL_TEXTURE3,
	GL_TEXTURE4,
	GL_TEXTURE5,
	GL_TEXTURE6,
	GL_TEXTURE7,
	GL_TEXTURE8,
	GL_TEXTURE9,
	GL_TEXTURE10,
	GL_TEXTURE11,
};

Texture::Texture(std::string fileLoc)
	: id(0), width(0), height(0), bitDepth(0), fileLocation(std::move(fileLoc))
{
}

void Texture::create(std::string fileLoc)
{
	if (id != 0) clear();
	fileLocation = std::move(fileLoc);
	id = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
}

bool Texture::load()
{
	unsigned char* data = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
	if (!data)
	{
		std::cout << "failed to find texture location: " << fileLocation << "\n";
		return false;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return true;
}

void Texture::use()
{
	glActiveTexture(textureIndexes[currentHighestTextureIndex]);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::clear()
{
	glDeleteTextures(1, &id);
	id = 0; width = 0; height = 0; fileLocation = "";
}