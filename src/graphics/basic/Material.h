#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "ShaderProgram.h"
#include "../uniforms/Uniform1f.h"
#include "../uniforms/Uniform3f.h"
#include "../uniforms/Uniform1i.h"
#include "../uniforms/UniformMat4.h"

class Material
{
public:
	Material(ShaderProgram* shaderProgram, const std::string& name);
	~Material();

	const std::string& getName() { return this->name; }

	template <class UNIFORM_TYPE, typename VALUE_TYPE>
	void setUniform(const std::string& name, VALUE_TYPE value);

	void renderUI()
	{
		for (auto u : uniforms)
		{
			u.second->renderUI();
		}
	}

private:

	ShaderProgram* shader;
	std::string name;

	std::unordered_map<std::string, Uniform*> uniforms;

	inline Uniform* getUniform(const std::string& name)
	{
		Uniform* u = uniforms[name];
		if (u == nullptr)
		{
			std::cout << "Could not find uniform: " << name << " in material: " << this->name << "\n";
		}
		return u;
	}

};