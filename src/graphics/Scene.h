#pragma once
#include "Model.h"
#include "Shader.h"
#include "light/DirectionalLight.h"
#include "light/Light.h"

class Scene
{
public:
	Scene(const std::string& vshader, const std::string& fshader);
	~Scene();

	void createNewShader(const std::string& vshader, const std::string& fshader);

	void addModel(Model* model);
	std::vector<Model*> getModels() { return this->models; }
	void deleteModel(size_t index);
	int getIndexOfFirstNonNullModel() const
	{
		for (int i = 0; i < models.size(); i++)
			if (models[i] != nullptr) return i;
		return -1;
	}
	void render();

	void renderLightsUi();
	void renderMaterialsUi();

	std::string getFragmentShaderSource() const { return shader->getFShader(); }
	std::string getVertexShaderSource() const { return shader->getVShader(); }
	Shader* getShader() { return shader; }
	bool doesModelNameExist(std::string& name);

private:
	Shader* shader;
	std::vector<Model*> models;
	std::vector<Light*> lights;
	DirectionalLight* directionalLight;
	Texture* missingTexture;
};

