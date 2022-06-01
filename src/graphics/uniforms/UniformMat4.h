#pragma once

#include <glm/glm.hpp>
#include "Uniform.h"

class UniformMat4 : public Uniform
{
public:
	UniformMat4(const std::string& n)
	: Uniform(n), value(glm::mat4())
	{}
	void set(const glm::mat4 mat);

	void bind() override;
private:
	glm::mat4 value;
};

