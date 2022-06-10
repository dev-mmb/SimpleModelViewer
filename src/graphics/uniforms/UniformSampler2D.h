#pragma once
#include <string>

#include "Uniform.h"
#include "../basic/Texture.h"

class UniformSampler2D : public Uniform
{
public:
	UniformSampler2D(const std::string& n)
		: Uniform(n), texture(nullptr)
	{}

	void set(Texture* texture);

	void bind() override;

private:
	Texture* texture;
};

