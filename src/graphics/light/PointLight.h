#pragma once
#include <string>

#include "Light.h"


class PointLight final : public Light
{
public:
	PointLight(Shader* shader, const std::string& name);
	~PointLight();

	static const std::string POSITION;
	static const std::string CONSTANT;
	static const std::string LINEAR;
	static const std::string QUADRATIC;

	static const std::string AMBIENT;
	static const std::string DIFFUSE;
	static const std::string SPECULAR;

	static constexpr int MAX_POINT_LIGHTS = 1;

	void renderModel(Shader* shader) override;

};

