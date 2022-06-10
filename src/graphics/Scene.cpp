#include "Scene.h"

#include "uniforms/Uniform1f.h"

Scene::Scene(const std::string& vshader, const std::string& fshader)
{
	createNewShader(vshader, fshader);
}

Scene::~Scene()
{
	delete shader;
}

void Scene::createNewShader(const std::string& vshader, const std::string& fshader)
{
	if (shader != nullptr)
	{
		delete shader;
	}
	this->shader = new Shader(vshader, fshader);

	shader->addMaterial("material");
	shader->getMaterial("material").setUniform<Uniform1f, float>("specular", 5);
	shader->getMaterial("material").setUniform<Uniform1f, float>("shine", 32);

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
	this->models.push_back(model);
}

void Scene::render()
{
	for (auto* model : models)
	{
		model->render(shader);
	}
}

void Scene::renderMaterialsUi()
{
	shader->renderMaterialsUi();
}