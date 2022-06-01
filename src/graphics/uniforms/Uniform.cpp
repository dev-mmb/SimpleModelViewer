#include "Uniform.h"

Uniform::Uniform(std::string name)
	: location(0), name(std::move(name))
{}

void Uniform::compile(GLuint shaderId)
{
	location = glGetUniformLocation(shaderId, name.c_str());
}

void Uniform::unBind()
{
	location = 0;
}
