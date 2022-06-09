#include "Uniform1f.h"

#include <imgui/imgui.h>

void Uniform1f::set(float v)
{
	value = v;
}

void Uniform1f::renderUI()
{
	ImGui::DragFloat(getUniqueDisplayName().c_str(), &value);
}

void Uniform1f::bind()
{
	glUniform1f(location, value);
}
