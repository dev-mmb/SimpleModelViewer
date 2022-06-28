#include "ApplicationController.h"
#include "Editor.h"
#include "graphics/uniforms/Uniform1f.h"
#include "graphics/uniforms/Uniform3f.h"


ApplicationController::ApplicationController() 
{

	scene = new Scene(vertexShaderSource, fragmentShaderSource);
	scene->addModel(new Model("model", "assets/models/Crate/Crate1.obj"));

	materialWidget = new ScenePropertiesWidget(scene);
}

ApplicationController::~ApplicationController()
{
	delete scene;
}

void ApplicationController::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();
}
