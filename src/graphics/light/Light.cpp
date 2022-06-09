#include "Light.h"

Light::Light(Shader* shader, const std::string& name)
{
	this->name = name; this->shader = shader;
}
