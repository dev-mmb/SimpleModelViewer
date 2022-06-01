#include "Uniform3f.h"

#include <imgui/imgui.h>

void Uniform3f::set(const glm::vec3 vec)
{
	value = vec;
}

void Uniform3f::renderUI()
{
	float vec[3] = { value.x, value.y, value.z };
	ImGui::DragFloat3(getNameWithoutMaterialName().c_str(), vec);
	value.x = vec[0]; value.y = vec[1]; value.z = vec[2];
}

void Uniform3f::bind()
{
	glUniform3f(location, value.x, value.y, value.z);
}
