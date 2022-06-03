#include "Material.h"

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

