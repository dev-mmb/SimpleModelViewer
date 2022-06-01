#pragma once
#include "basic/Material.h"
#include "basic/ShaderProgram.h"

class Shader
{
public:
	Shader(const std::string& vshader, const std::string& fshader);
	~Shader();

	void addMaterial(const std::string& name);
	Material& getMaterial(const std::string& name);
	void addUniform(Uniform* uniform);
	void bind();
	void unBind();
	void compile();

	void setModel(const glm::mat4& m) { model.set(m); }

private:
	ShaderProgram* shaderProgram;
	std::vector<Material*> materials;
	UniformMat4 model, projection, view;
	Uniform3f viewPosition;
};