#pragma once
#include "Widget.h"
#include <imgui/imgui.h>
#include <vector>
#include "../graphics/Model.h"
#include "../graphics/Scene.h"
#include <L2DFileDialog/L2DFileDialog.h>


class ScenePropertiesWidget : public Widget
{
public:
	ScenePropertiesWidget(Scene* scene) : Widget(userInterface)
	{
		this->scene = scene;
	}

	void render() override
	{
		ImGui::Begin("Properties");
		ImGui::BeginTabBar("tab_bar");
		if (ImGui::BeginTabItem("Models"))
		{
			modelSelectUi();
			propertiesUi(scene->getModels()[selectedModel]);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Shader"))
		{
			shadersUi();
			materialsUi();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		ImGui::End();
	}

private:
	Scene* scene;
	size_t selectedModel = 0;
	std::string currentPath = "";
	bool vertexIsOpen = false, fragmentIsOpen = false;

	void modelSelectUi()
	{
		ImGui::BeginListBox("Models");
		for (size_t i = 0; i < scene->getModels().size(); i++)
		{
			Model* m = scene->getModels()[i];
			if (ImGui::RadioButton(m->getname().c_str(), i == selectedModel))
			{
				selectedModel = i;
			}
		}
		ImGui::EndListBox();
	}

	bool validateShaderPath(const std::string& path)
	{
		if (path == scene->getFragmentShaderSource() || path == scene->getVertexShaderSource()) return false;
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

	void propertiesUi(Model* mesh)
	{
		if (ImGui::CollapsingHeader("properties"))
		{
			float vec[3] = { mesh->getPosition().x, mesh->getPosition().y, mesh->getPosition().z };
			ImGui::DragFloat3("Position", vec, 0.01f);
			mesh->setPosition(glm::vec3{ vec[0], vec[1], vec[2] });

			vec[0] = mesh->getRotation().x; vec[1] = mesh->getRotation().y; vec[2] = mesh->getRotation().z;
			ImGui::DragFloat3("Rotation", vec);
			mesh->setRotation(glm::vec3{ vec[0], vec[1], vec[2] });

			vec[0] = mesh->getScale().x; vec[1] = mesh->getScale().y; vec[2] = mesh->getScale().z;
			ImGui::DragFloat3("Scale", vec, 0.01f);
			mesh->setScale(glm::vec3{ vec[0], vec[1], vec[2] });
		}
	}

	void materialsUi()
	{
		if (ImGui::CollapsingHeader("materials"))
		{
			scene->renderMaterialsUi();
		}
	}

	void shadersUi()
	{
		if (ImGui::CollapsingHeader("shaders"))
		{
			if (ImGui::Button("Fragment Shader")) {
				FileDialog::file_dialog_open = true;
				FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
				vertexIsOpen = false;
				fragmentIsOpen = true;
			}
			ImGui::SameLine();
			ImGui::Text(scene->getFragmentShaderSource().c_str());

			if (ImGui::Button("Vertex Shader")) {
				FileDialog::file_dialog_open = true;
				FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
				vertexIsOpen = true;
				fragmentIsOpen = false;
			}
			ImGui::SameLine();
			ImGui::Text(scene->getVertexShaderSource().c_str());

			if (FileDialog::file_dialog_open) {
				FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, currentPath, FileDialog::file_dialog_open_type);

				if (!currentPath.empty())
				{
					if (validateShaderPath(currentPath))
					{
						if (vertexIsOpen)
							scene->createNewShader(currentPath, scene->getFragmentShaderSource());
						else if (fragmentIsOpen)
							scene->createNewShader(scene->getVertexShaderSource(), currentPath);
						vertexIsOpen = false;
						fragmentIsOpen = false;
					}

				}
			}
		}
	}
};