#include "PointLight.h"
#include "../BasicModels.h"

class Uniform1f;
const std::string PointLight::POSITION = "pos";

const std::string PointLight::CONSTANT = "constant";
const std::string PointLight::LINEAR = "linear";
const std::string PointLight::QUADRATIC = "quadratic";

const std::string PointLight::AMBIENT = "ambient";
const std::string PointLight::DIFFUSE = "diffuse";
const std::string PointLight::SPECULAR = "specular";

constexpr int PointLight::MAX_POINT_LIGHTS;

PointLight::PointLight(Shader* shader, const std::string& name)
: Light(shader, name, BasicModels::basicCube("assets/textures/light.png", 0))
{
	model->setScale(glm::vec3(0.02f));

	shader->addMaterial(name);
	Material& m = shader->getMaterial(name);
	m.setUniform<Uniform3f, glm::vec3>(POSITION, glm::vec3(0, 0, 0));

	m.setUniform<Uniform1f, float>(CONSTANT, 1);
	m.setUniform<Uniform1f, float>(LINEAR, 0.09f);
	m.setUniform<Uniform1f, float>(QUADRATIC, 0.032f);

	m.setUniform<Uniform3f, glm::vec3>(AMBIENT, glm::vec3(1, 0.5, 0));
	m.setUniform<Uniform3f, glm::vec3>(DIFFUSE, glm::vec3(1, 0.5, 0));
	m.setUniform<Uniform3f, glm::vec3>(SPECULAR, glm::vec3(1, 0.5, 0));
}

PointLight::~PointLight()
{
	delete model;
}

void PointLight::renderModel(Shader* shader)
{
	Material& m = shader->getMaterial(name);
	Uniform* u = m.getUniform(name + "." + POSITION);
	Uniform3f* u3f = dynamic_cast<Uniform3f*>(u);
	model->setPosition(u3f->get());
	model->render(shader);
}


