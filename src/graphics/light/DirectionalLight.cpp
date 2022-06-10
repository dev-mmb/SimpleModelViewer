#include "DirectionalLight.h"

#include "../uniforms/Uniform1f.h"
#include "../uniforms/Uniform3f.h"

const std::string DirectionalLight::DIFFUSE_NAME = "diffuse";
const std::string DirectionalLight::AMBIENT_NAME = "ambient";
const std::string DirectionalLight::DIRECTION_NAME = "direction";

DirectionalLight::DirectionalLight(Shader* shader, const std::string& name) : Light(shader, name)
{
	shader->addMaterial(name);
	Material& m = shader->getMaterial(name);
	m.setUniform<Uniform3f, glm::vec3>(DIRECTION_NAME, glm::vec3(2, -1, -2));
	m.setUniform<Uniform3f, glm::vec3>(DIFFUSE_NAME, glm::vec3(0.4f, 0.3f, 0.0f));
	m.setUniform<Uniform3f, glm::vec3>(AMBIENT_NAME, glm::vec3(0.4f, 0.3f, 0.0f));
}
