#include "PointLight.h"

class Uniform1f;
const std::string PointLight::POSITION = "pos";
const std::string PointLight::COLOR = "color";
const std::string PointLight::CONSTANT = "constant";
const std::string PointLight::LINEAR = "linear";
const std::string PointLight::QUADRATIC = "quadratic";
constexpr int PointLight::MAX_POINT_LIGHTS;

PointLight::PointLight(Shader* shader, const std::string& name) : Light(shader, name)
{
	shader->addMaterial(name);
	Material& m = shader->getMaterial(name);
	m.setUniform<Uniform3f, glm::vec3>(POSITION, glm::vec3(0, 0, 0));
	m.setUniform<Uniform3f, glm::vec3>(COLOR, glm::vec3(0, 0, 0));

	m.setUniform<Uniform1f, float>(CONSTANT, 1);
	m.setUniform<Uniform1f, float>(LINEAR, 0.09f);
	m.setUniform<Uniform1f, float>(QUADRATIC, 0.032f);
}
