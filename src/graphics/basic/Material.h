#pragma once

#include <unordered_map>
#include <string>

#include "ShaderProgram.h"


class Material
{
public:
	Material(ShaderProgram* shaderProgram, const std::string& name);
	~Material();

	const std::string& getName() { return this->name; }

	template <class UNIFORM_TYPE, typename VALUE_TYPE>
	void setUniform(const std::string& name, VALUE_TYPE value)
	{
		shader->setUniform<UNIFORM_TYPE, VALUE_TYPE>(this->name + "." + name, value);
	}
	Uniform* getUniform(const std::string& name)
	{
		return &shader->getUniform(name);
	}

	void renderUi();

private:
	ShaderProgram* shader;
	std::string name;

	std::unordered_map<std::string, int> uniforms;
};
