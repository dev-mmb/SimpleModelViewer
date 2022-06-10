#pragma once
#include "Model.h"
#include "Shader.h"

class Scene
{
public:
	Scene(const std::string& vshader, const std::string& fshader);
	~Scene();

	void createNewShader(const std::string& vshader, const std::string& fshader);

	void addModel(Model* model);
	std::vector<Model*> getModels() { return this->models; }
	void render();
	void renderMaterialsUi();

	std::string getFragmentShaderSource() const { return shader->getFShader(); }
	std::string getVertexShaderSource() const { return shader->getVShader(); }

private:
	Shader* shader;
	std::vector<Model*> models;
	std::vector<Light*> lights;
	DirectionalLight* directionalLight;
};

