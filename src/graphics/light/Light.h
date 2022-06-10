#pragma once
#include <string>
#include "../Shader.h"
#include "../Model.h"

class Light
{
public:
	virtual ~Light() = default;
	Light(Shader* shader, const std::string& name, Model* model);

	virtual void renderModel(Shader* shader) {}
	void renderUi();
protected:
	std::string name;
	Shader* shader;
	Model* model;
};

