#pragma once
#include "Widget.h"
#include <imgui/imgui.h>
#include <vector>
#include "../graphics/Model.h"
#include "../graphics/Scene.h"
#include <L2DFileDialog/L2DFileDialog.h>

#include "ModelWidget.h"


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
			if (selectedModel != -1)
				propertiesUi(scene->getModels()[selectedModel]);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Shader"))
		{
			shadersUi();
			sceneUi();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		ImGui::End();
	}

private:
	Scene* scene;
	int selectedModel = 0;
	std::string currentPath = "", currentModelPath;
	ModelWidgetExtension modelWidgetExtension;
	bool vertexIsOpen = false, fragmentIsOpen = false, importModelIsOpen = false;

	void modelSelectUi()
	{
		if (ImGui::Button("Import model"))
		{
			FileDialog::file_dialog_open = true;
			FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
			importModelIsOpen = true;
		}
		if (FileDialog::file_dialog_open && importModelIsOpen)
		{
			FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, currentModelPath, FileDialog::file_dialog_open_type);

			if (!currentModelPath.empty())
			{
				scene->addModel(new Model(generateName(currentModelPath), currentModelPath));
				importModelIsOpen = false;
				currentModelPath = "";
			}
		}

		ImGui::BeginListBox("Models");
		for (size_t i = 0; i < scene->getModels().size(); i++)
		{
			Model* m = scene->getModels()[i];
			if (m != nullptr)
			{
				if (ImGui::RadioButton(m->getName().c_str(), i == selectedModel))
				{
					selectedModel = i;
				}
				ImGui::SameLine();
				if (ImGui::Button(("Delete " + m->getName()).c_str()))
				{
					scene->deleteModel(i);
					if (i == selectedModel)
					{
						selectedModel = scene->getIndexOfFirstNonNullModel();
					}
				}
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
		if (ImGui::CollapsingHeader("Material"))
		{
			modelWidgetExtension.render(mesh);
		}
	}

	void sceneUi()
	{
		if (ImGui::CollapsingHeader("Lights"))
		{
			scene->renderLightsUi();
		}
		if (ImGui::CollapsingHeader("Materials"))
		{
			scene->renderMaterialsUi();
		}
	}


	void shadersUi()
	{
		if (ImGui::CollapsingHeader("Shaders"))
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

	std::string generateName(const std::string& path)
	{
		size_t slashPos = path.find_last_of('/');
		if (slashPos == std::string::npos)
			slashPos = path.find_last_of('\\');
		if (slashPos == std::string::npos)
			return path;

		std::string name;
		size_t dotpos = path.find('.');
		if (dotpos != std::string::npos)
			name = path.substr(slashPos + 1, dotpos - slashPos - 1);
		else name = path.substr(slashPos);

		std::string newName = name;
		int count = 0;
		while (true)
		{
			if (!scene->doesModelNameExist(newName)) return newName;
			newName = name + "(" + std::to_string(++count) + ")";
		}
	}
};
