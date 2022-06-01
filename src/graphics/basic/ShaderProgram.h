#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glew.h>
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

	void addUniform(Uniform* uniform) { uniforms.push_back(uniform); }
	std::vector<Uniform*> getAllUniformsFromMaterial(const std::string& materialName) const;
	
private:
	GLuint id;
	std::vector<Uniform*> uniforms;

	void compileShader(const std::string& vertexShader, const std::string& fragmentShader);
	void addShader(GLuint program, const std::string& code, GLenum shaderType);

	std::string readFile(const std::string& file);

	bool hasErrors(GLuint value);
	Uniform* createUniform(const std::string& name, GLenum type) const;

};

