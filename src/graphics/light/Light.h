#pragma once
#include <string>
#include "../Shader.h"

class Light
{
public:
	virtual ~Light() = default;
	Light(Shader* shader, const std::string& name);

	void renderUi();
protected:
	std::string name;
	Shader* shader;
};

