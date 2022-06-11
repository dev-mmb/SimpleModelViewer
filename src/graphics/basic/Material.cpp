#include "Material.h"

const std::vector<std::string> Material::RESERVED_MATERIAL_NAMES = std::vector<std::string>
{
	"material",
	"directionalLight",
	"pointLights",
	"pointLights[0]",
	"pointLights[1]",
	"pointLights[2]",
	"pointLights[3]",
	"pointLights[4]",
	"pointLights[5]",
	"pointLights[6]",
	"pointLights[7]",
	"pointLights[8]",
	"pointLights[9]",
};

Material::Material(ShaderProgram* shaderProgram, const std::string& name)
{
	this->shader = shaderProgram;
	this->name = name;

	this->uniforms = this->shader->getAllUniformsFromMaterial(this->name);
}

Material::~Material()
{
	uniforms.clear();
}

void Material::renderUi()
{
	for (auto u : uniforms)
	{
		auto& uniform = shader->getUniform(u.second);
		uniform.renderUI();
	}
}

