#pragma once
#include "Widget.h"
#include <imgui/imgui.h>
#include <vector>
#include "../graphics/basic/Material.h"

class MaterialWidget : public Widget
{
public:
	MaterialWidget(Material* material) : Widget(userInterface)
	{
		this->materials.push_back(material);
	}

	void addMaterial(Material* material)
	{
		materials.push_back(material);
	}

	void render() override
	{
		ImGui::Begin("Materials");

		for (Material* material : materials)
		{
			ImGui::Text(material->getName().c_str());
			material->renderUI();
		}

		ImGui::End();
	}

private:
	std::vector<Material*> materials;
};
