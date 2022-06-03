#pragma once
#include <string>
#include <glm/vec3.hpp>

#include "Uniform.h"

class Uniform3f : public Uniform
{
public:
	Uniform3f(const std::string& n)
	: Uniform(n), value(glm::vec3())
	{}

	void set(const glm::vec3 vec);
	void renderUI() override;

	void bind() override;
private:
	glm::vec3 value;
};

