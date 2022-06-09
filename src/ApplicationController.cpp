#include "ApplicationController.h"
#include "Editor.h"
#include "graphics/uniforms/Uniform1f.h"
#include "graphics/uniforms/Uniform3f.h"


ApplicationController::ApplicationController() 
{
	mesh = new Model(vertexShaderSource, fragmentShaderSource, createTriangle()[0]);

	auto shader = new Shader(vertexShaderSource, fragmentShaderSource);

	shader->addMaterial("material");
	shader->getMaterial("material").setUniform<Uniform1f, float>("specularIntensity", 5);
	shader->getMaterial("material").setUniform<Uniform1f, float>("shine", 32);

	shader->compile();

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
