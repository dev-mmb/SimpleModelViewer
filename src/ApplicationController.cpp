#include "ApplicationController.h"
#include "Editor.h"
#include "graphics/uniforms/Uniform1f.h"
#include "graphics/uniforms/Uniform3f.h"


ApplicationController::ApplicationController() 
{
	mesh = new StaticMesh(vertexShaderSource, fragmentShaderSource, createTriangle()[0]);
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
