#include "ApplicationController.h"
#include "Editor.h"
#include "graphics/uniforms/Uniform1f.h"
#include "graphics/uniforms/Uniform3f.h"


ApplicationController::ApplicationController() 
{

	auto shader = new Shader(vertexShaderSource, fragmentShaderSource);

	shader->addMaterial("material");
	shader->addMaterial("directionalLight");
	shader->getMaterial("material").setUniform<Uniform1f, float>("specularIntensity", 5);
	shader->getMaterial("material").setUniform<Uniform1f, float>("shine", 32);

	shader->getMaterial("directionalLight").setUniform<Uniform1f, float>("diffuseIntensity", 3);
	shader->getMaterial("directionalLight").setUniform<Uniform1f, float>("ambientIntensity", 3);
	shader->getMaterial("directionalLight").setUniform<Uniform3f, glm::vec3>("direction", glm::vec3(2, -1, -2));
	shader->getMaterial("directionalLight").setUniform<Uniform3f, glm::vec3>("color", glm::vec3(0.4f, 0.3f, 0.0f));

	shader->compile();

	mesh = new StaticMesh(shader, createTriangle()[0]);
	materialWidget = new StaticMeshPropertiesWidget(mesh);
}

ApplicationController::~ApplicationController()
{
	delete mesh;
}

void ApplicationController::save()
{
}

void ApplicationController::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mesh->render();
}
