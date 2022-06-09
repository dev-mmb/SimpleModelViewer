#pragma once
#include <string>

#include "Light.h"


class PointLight : public Light
{
public:
	PointLight(Shader* shader, const std::string& name);

	static const std::string POSITION;
	static const std::string COLOR;
	static const std::string CONSTANT;
	static const std::string LINEAR;
	static const std::string QUADRATIC;
	static constexpr int MAX_POINT_LIGHTS = 1;
};

