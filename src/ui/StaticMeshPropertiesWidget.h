#pragma once
#include "Widget.h"
#include <imgui/imgui.h>
#include <vector>
#include "../graphics/StaticMesh.h"

class StaticMeshPropertiesWidget : public Widget
{
public:
	StaticMeshPropertiesWidget(StaticMesh* mesh) : Widget(userInterface)
	{
		this->mesh = mesh;
	}


	void render() override
	{
		ImGui::Begin("Properties");

		float vec[3] = { mesh->getPosition().x, mesh->getPosition().y, mesh->getPosition().z };
		ImGui::DragFloat3("Position", vec);
		mesh->setPosition(glm::vec3{ vec[0], vec[1], vec[2] });

		vec[0] = mesh->getRotation().x; vec[1] = mesh->getRotation().y; vec[2] = mesh->getRotation().z;
		ImGui::DragFloat3("Rotation", vec);
		mesh->setRotation(glm::vec3{ vec[0], vec[1], vec[2] });

		vec[0] = mesh->getScale().x; vec[1] = mesh->getScale().y; vec[2] = mesh->getScale().z;
		ImGui::DragFloat3("Scale", vec);
		mesh->setScale(glm::vec3{ vec[0], vec[1], vec[2] });

		ImGui::Text("Materials");
		mesh->renderMaterialsUi();

		ImGui::End();
	}

private:
	StaticMesh* mesh;
};
