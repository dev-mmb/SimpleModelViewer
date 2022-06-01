#include "Uniform3f.h"

void Uniform3f::set(const glm::vec3 vec)
{
	value = vec;
}

void Uniform3f::bind()
{
	glUniform3f(location, value.x, value.y, value.z);
}
