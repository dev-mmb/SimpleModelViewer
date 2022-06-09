#include "DirectionalLight.h"

#include "../uniforms/Uniform1f.h"
#include "../uniforms/Uniform3f.h"

const std::string DirectionalLight::DIFFUSE_INTENSITY_NAME = "diffuseIntensity";
const std::string DirectionalLight::AMBIENT_INTENSITY_NAME = "ambientIntensity";
const std::string DirectionalLight::DIRECTION_NAME = "direction";
const std::string DirectionalLight::COLOR_NAME = "color";

DirectionalLight::DirectionalLight(Shader* shader, const std::string& name) : Light(shader, name)
{
	shader->addMaterial(name);
	Material& m = shader->getMaterial(name);
	m.setUniform<Uniform1f, float>(DIFFUSE_INTENSITY_NAME, 3);
	m.setUniform<Uniform1f, float>(AMBIENT_INTENSITY_NAME, 3);
	m.setUniform<Uniform3f, glm::vec3>(DIRECTION_NAME, glm::vec3(2, -1, -2));
	m.setUniform<Uniform3f, glm::vec3>(COLOR_NAME, glm::vec3(0.4f, 0.3f, 0.0f));
}
