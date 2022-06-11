#pragma once
#include "Widget.h"
#include "../graphics/Model.h"
#include "imgui/imgui.h"
#include "L2DFileDialog/L2DFileDialog.h"

class ModelWidgetExtension
{
public:
	ModelWidgetExtension()
	{
	}

	void render(Model* model)
	{
		float vec[3] = { model->getPosition().x, model->getPosition().y, model->getPosition().z };
		ImGui::DragFloat3("Position", vec, 0.01f);
		model->setPosition(glm::vec3{ vec[0], vec[1], vec[2] });

		vec[0] = model->getRotation().x; vec[1] = model->getRotation().y; vec[2] = model->getRotation().z;
		ImGui::DragFloat3("Rotation", vec);
		model->setRotation(glm::vec3{ vec[0], vec[1], vec[2] });

		vec[0] = model->getScale().x; vec[1] = model->getScale().y; vec[2] = model->getScale().z;
		ImGui::DragFloat3("Scale", vec, 0.01f);
		model->setScale(glm::vec3{ vec[0], vec[1], vec[2] });

		ImGui::BulletText("Material");
		float shine = model->getShine();
		ImGui::DragFloat(Model::SHINE_NAME.c_str(), &shine, 0.01f);
		model->setShine(shine);


		ImGui::BulletText("Textures");
		for (size_t i = 0; i < model->getDiffuseMaps().size(); i++)
		{
			if (ImGui::Button(getButtonName(model->getDiffuseMaps()[i], "diffuse map", i).c_str()))
			{
				FileDialog::file_dialog_open = true;
					FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
					openTexture = model->getDiffuseMaps()[i];
			}
			if (ImGui::Button(getButtonName(model->getSpecularMaps()[i], "specular map", i).c_str()))
			{
				FileDialog::file_dialog_open = true;
					FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
					openTexture = model->getSpecularMaps()[i];
			}
		}

		if (FileDialog::file_dialog_open)
		{
			FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, currentPath, FileDialog::file_dialog_open_type);

			if (!currentPath.empty())
			{
				openTexture->create(currentPath);
				openTexture->load();
				currentPath = "";
			}
		}
	}

private:
	std::string currentPath;
	Texture* openTexture = nullptr;

	std::string getButtonName(Texture* t, std::string n, int num)
	{
		return n + ": " + std::to_string(num) + ", " + t->getFileLocation();
	}
};
