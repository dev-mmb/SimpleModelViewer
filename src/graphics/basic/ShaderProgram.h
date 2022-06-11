#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glew.h>
#include <unordered_map>
#include <vector>

#include "../uniforms/Uniform.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void createFromString(const std::string& vertexShader, const std::string& fragmentShader);
	void createFromFile(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);

	void compile();
	void bind();
	void unBind();

	template <class UNIFORM_TYPE, typename VALUE_TYPE>
	void setUniform(const std::string& name, VALUE_TYPE value);

	void addUniform(Uniform* uniform)
	{
		uniforms.push_back(uniform);
	}

	std::unordered_map<std::string, int> getAllUniformsFromMaterial(const std::string& materialName) const;

	Uniform& getUniform(int i)
	{
		return *uniforms[i];
	}
	// returns the first uniform if not found
	Uniform& getUniform(const std::string& name) { return *getUniformPointer(name); }

	std::vector<std::string> getAllMaterialNames() const;
	
private:
	GLuint id;
	std::vector<Uniform*> uniforms;

	void compileShader(const std::string& vertexShader, const std::string& fragmentShader);
	void addShader(GLuint program, const std::string& code, GLenum shaderType);
	std::string readFile(const std::string& file);
	bool hasErrors(GLuint value);

	void createUniform(const std::string& name, GLenum type);
	void getAllUniforms();

	inline Uniform* getUniformPointer(const std::string& name)
	{
		for (auto u : this->uniforms)
		{
			if (u->getName() == name)
				return u;
		}
		std::cout << "Could not find uniform: " << name << "\n";
		return nullptr;
	}
};

