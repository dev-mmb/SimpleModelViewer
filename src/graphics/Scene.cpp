#include "Scene.h"

#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "uniforms/Uniform1f.h"

class UniformSampler2D;

Scene::Scene(const std::string& vshader, const std::string& fshader)
{
	createNewShader(vshader, fshader);
	missingTexture = new Texture("/assets/textures/missing.png", Model::DIFFUSE_NAME);
}

Scene::~Scene()
{
	delete shader;
	delete missingTexture;
}

void Scene::createNewShader(const std::string& vshader, const std::string& fshader)
{
	if (shader != nullptr)
	{
		delete shader;
	}
	this->shader = new Shader(vshader, fshader);

	shader->addMaterial("material");
	shader->getMaterial("material").setUniform<Uniform1f, float>(Model::SHINE_NAME, 32);
	shader->getMaterial("material").setUniform<UniformSampler2D, Texture*>(Model::SPECULAR_NAME, missingTexture);
	shader->getMaterial("material").setUniform<UniformSampler2D, Texture*>(Model::DIFFUSE_NAME, missingTexture);

	directionalLight = new DirectionalLight(shader, "directionalLight");

	for (size_t i = 0; i < PointLight::MAX_POINT_LIGHTS; i++)
	{
		std::string name = "pointLights[";
		lights.push_back(new PointLight{ shader, name + std::to_string(i) + std::string("]") });
	}

	shader->compile();
}

void Scene::addModel(Model* model)
{
	for (size_t i = 0; i < models.size(); i++)
	{
		if (models[i] == nullptr)
		{
			models[i] = model;
			return;
		}

	}
	this->models.push_back(model);
}

void Scene::deleteModel(size_t index)
{
	delete models[index];
	models[index] = nullptr;
}

void Scene::render()
{
	for (auto* model : models)
	{
		if (model != nullptr)
			model->render(shader);
	}
	for (auto* light : lights)
	{
		light->renderModel(shader);
	}
}

void Scene::renderLightsUi()
{
	for (Light* light : lights)
	{
		light->renderUi();
	}
	directionalLight->renderUi();
}

void Scene::renderMaterialsUi()
{
	shader->renderMaterialsUi();
}

bool Scene::doesModelNameExist(std::string& name)
{
	for (Model* m : models)
	{
		if (m != nullptr && m->getName() == name)
			return true;
	}
	return false;
}
