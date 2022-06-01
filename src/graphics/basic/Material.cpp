#include "Material.h"

Material::Material(ShaderProgram* shaderProgram, const std::string& name)
{
	this->shader = shaderProgram;
	this->name = name;

	const std::vector<Uniform*> uniforms = this->shader->getAllUniformsFromMaterial(this->name);
	for (Uniform* uniform : uniforms)
	{
		this->uniforms[uniform->getName().substr(uniform->getName().find('.') + 1)] = uniform;
		this->shader->addUniform(uniform);
	}

}

Material::~Material()
{
	for (auto& uniform : uniforms)
	{
		delete uniform.second;
		uniform.second = nullptr;
	}
	uniforms.clear();
}



template <class UNIFORM_TYPE, typename VALUE_TYPE>
void Material::setUniform(const std::string& name, VALUE_TYPE value)
{}
template<>
void Material::setUniform<Uniform1f, float>(const std::string& name, float value)
{
	Uniform* u = getUniform(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform1f*>(u);
	castedUniform->set(value);
}
template<>
void Material::setUniform<Uniform1i, int>(const std::string& name, int value)
{
	Uniform* u = getUniform(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform1i*>(u);
	castedUniform->set(value);
}
template<>
void Material::setUniform<Uniform3f, glm::vec3>(const std::string& name, glm::vec3 value)
{
	Uniform* u = getUniform(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<Uniform3f*>(u);
	castedUniform->set(value);
}
template<>
void Material::setUniform<UniformMat4, glm::mat4>(const std::string& name, glm::mat4 value)
{
	Uniform* u = getUniform(name);
	if (u == nullptr) return;
	auto castedUniform = dynamic_cast<UniformMat4*>(u);
	castedUniform->set(value);
}