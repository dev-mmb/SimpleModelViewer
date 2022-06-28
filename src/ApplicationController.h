#pragma once
#include <string>
#include <vector>

#include "graphics/Model.h"

#include "ui/ScenePropertiesWidget.h"
#include "graphics/BasicModels.h"

class ApplicationController
{
public:
	ApplicationController();
	~ApplicationController();
	void render();

private:
	std::string vertexShaderSource = "assets/vertexShader.glsl";

	std::string fragmentShaderSource = "assets/fragmentShader.glsl";

	ScenePropertiesWidget* materialWidget;
	Scene* scene;

	Model* createTriangle()
	{
		return BasicModels::basicTriangle();
	}
};

