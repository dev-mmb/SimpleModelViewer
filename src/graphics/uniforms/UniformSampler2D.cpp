#include "UniformSampler2D.h"

void UniformSampler2D::set(Texture* texture)
{
	this->texture = texture;
	bind();
}

void UniformSampler2D::bind()
{
	if (texture != nullptr)
		this->texture->use();
}
