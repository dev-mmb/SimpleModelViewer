#pragma once
#include <string>
#include "../Shader.h"

class Light
{
public:
	virtual ~Light() = default;
	Light(Shader* shader, const std::string& name);

private:
	std::string name;
	Shader* shader;
};

