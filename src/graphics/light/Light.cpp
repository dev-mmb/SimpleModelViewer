#include "Light.h"

#include "imgui/imgui.h"

Light::Light(Shader* shader, const std::string& name, Model* model)
{
	this->name = name; this->shader = shader; this->model = model;
}


void Light::renderUi()
{
	ImGui::BulletText(name.c_str());
	shader->getMaterial(name).renderUi();
}

