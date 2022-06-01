#include "Uniform1f.h"

void Uniform1f::set(float v)
{
	value = v;
}

void Uniform1f::bind()
{
	glUniform1f(location, value);
}
