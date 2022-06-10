#include "Light.h"

#include "imgui/imgui.h"

Light::Light(Shader* shader, const std::string& name)
{
	this->name = name; this->shader = shader;
}

void Light::renderUi()
{
	ImGui::BulletText(name.c_str());
	shader->getMaterial(name).renderUi();
}

