#include "UniformMat4.h"

#include <glew.h>
#include <glm/gtc/type_ptr.inl>

void UniformMat4::set(const glm::mat4 mat)
{
	value = mat;
}

void UniformMat4::bind()
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
