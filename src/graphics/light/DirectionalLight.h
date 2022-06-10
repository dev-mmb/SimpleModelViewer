#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(Shader* shader, const std::string& name);

	static const std::string DIFFUSE_NAME;
	static const std::string AMBIENT_NAME;
	static const std::string DIRECTION_NAME;
	static const std::string SPECULAR_NAME;
};

