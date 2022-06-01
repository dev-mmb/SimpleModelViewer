#include "Shader.h"
#include "../Editor.h"

Shader::Shader(const std::string& vshader, const std::string& fshader) :
	model(UniformMat4("model")),
	projection(UniformMat4("projection")),
	view(UniformMat4("view")),
	viewPosition(Uniform3f("viewPosition"))
{
	shaderProgram = new ShaderProgram();

	projection.set(EditorData::getProjectionMatrix());
	view.set(EditorData::getViewMatrix());
	viewPosition.set(EditorData::getViewPosition());

	shaderProgram->addUniform(&model);
	shaderProgram->addUniform(&view);
	shaderProgram->addUniform(&projection);
	shaderProgram->addUniform(&viewPosition);

	shaderProgram->createFromFile(vshader, fshader);

}

Shader::~Shader()
{
	delete shaderProgram;
	for (Material* material : materials)
	{
		delete material;
	}
}

void Shader::addMaterial(const std::string& name)
{
	auto material = new Material(shaderProgram, name);
	materials.push_back(material);
}

Material& Shader::getMaterial(const std::string& name)
{
	for (Material* m : materials)
	{
		if (m->getName() == name)
		{
			return *m;
		}
	}
	std::cout << "could not find material with name: " << name << "\n";
	return *materials[0];
}

void Shader::addUniform(Uniform* uniform)
{
	shaderProgram->addUniform(uniform);
}

void Shader::bind()
{
	shaderProgram->bind();
	projection.set(EditorData::getProjectionMatrix());
	view.set(EditorData::getViewMatrix());
	viewPosition.set(EditorData::getViewPosition());
}

void Shader::unBind()
{
	shaderProgram->unBind();
}

void Shader::compile()
{
	this->shaderProgram->compile();
}