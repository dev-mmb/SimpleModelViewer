#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(Shader* shader, const std::string& name);

	static const std::string DIFFUSE_INTENSITY_NAME;
	static const std::string AMBIENT_INTENSITY_NAME;
	static const std::string DIRECTION_NAME;
	static const std::string COLOR_NAME;
};

