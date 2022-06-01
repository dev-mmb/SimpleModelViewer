#include "Uniform1i.h"

void Uniform1i::set(int v)
{
	value = v;
}

void Uniform1i::bind()
{
	glUniform1i(location, value);
}
