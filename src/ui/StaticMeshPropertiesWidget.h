#pragma once
#include "Widget.h"
#include <imgui/imgui.h>
#include <vector>
#include "../graphics/Model.h"
#include <L2DFileDialog/L2DFileDialog.h>

class StaticMeshPropertiesWidget : public Widget
{
public:
	StaticMeshPropertiesWidget(Model* mesh) : Widget(userInterface)
	{
		this->mesh = mesh;
	}


	void render() override
	{

		ImGui::Begin("Properties");
		if (ImGui::CollapsingHeader("shaders"))
		{
			if (ImGui::Button("Fragment Shader")) {
				FileDialog::file_dialog_open = true;
				FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
				vertexIsOpen = false;
				fragmentIsOpen = true;
			}
			ImGui::SameLine();
			ImGui::Text(mesh->getFragmentShaderSource().c_str());

			if (ImGui::Button("Vertex Shader")) {
				FileDialog::file_dialog_open = true;
				FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
				vertexIsOpen = true;
				fragmentIsOpen = false;
			}
			ImGui::SameLine();
			ImGui::Text(mesh->getVertexShaderSource().c_str());

			if (FileDialog::file_dialog_open) {
				FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, currentPath, FileDialog::file_dialog_open_type);

				if (!currentPath.empty())
				{
					if (validateShaderPath(currentPath))
					{
						if (vertexIsOpen)
							mesh->createNewShader(currentPath, mesh->getFragmentShaderSource());
						else if (fragmentIsOpen)
							mesh->createNewShader(mesh->getVertexShaderSource(), currentPath);
						vertexIsOpen = false;
						fragmentIsOpen = false;
					}

				}
			}
		}

		propertiesUi();
		materialsUi();

		ImGui::End();
	}

private:
	Model* mesh;
	std::string currentPath = "";
	bool vertexIsOpen = false, fragmentIsOpen = false;

	bool validateShaderPath(const std::string& path)
	{
		if (path == mesh->getFragmentShaderSource() || path == mesh->getVertexShaderSource()) return false;
		size_t dotpos = path.find('.');
		if (dotpos != std::string::npos)
		{

			if (path.substr(dotpos + 1) == "glsl")
			{

				if (vertexIsOpen)
					return path.find("vertex") != std::string::npos;
				if (fragmentIsOpen)
					return path.find("fragment") != std::string::npos;
			}
		}
		return false;
	}

	void propertiesUi()
	{
		if (ImGui::CollapsingHeader("properties"))
		{
			float vec[3] = { mesh->getPosition().x, mesh->getPosition().y, mesh->getPosition().z };
			ImGui::DragFloat3("Position", vec);
			mesh->setPosition(glm::vec3{ vec[0], vec[1], vec[2] });

			vec[0] = mesh->getRotation().x; vec[1] = mesh->getRotation().y; vec[2] = mesh->getRotation().z;
			ImGui::DragFloat3("Rotation", vec);
			mesh->setRotation(glm::vec3{ vec[0], vec[1], vec[2] });

			vec[0] = mesh->getScale().x; vec[1] = mesh->getScale().y; vec[2] = mesh->getScale().z;
			ImGui::DragFloat3("Scale", vec);
			mesh->setScale(glm::vec3{ vec[0], vec[1], vec[2] });
		}
	}

	void materialsUi()
	{
		if (ImGui::CollapsingHeader("materials"))
		{
			mesh->renderMaterialsUi();
		}
	}
};