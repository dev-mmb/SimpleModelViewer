#include "ApplicationController.h"
#include "Editor.h"
#include "graphics/uniforms/Uniform1f.h"
#include "graphics/uniforms/Uniform3f.h"


ApplicationController::ApplicationController() 
{

	scene = new Scene(vertexShaderSource, fragmentShaderSource);
	scene->addModel(BasicModels::basicCube("assets/textures/brick.png", 0));
	scene->addModel(BasicModels::basicCube("assets/textures/brick.png", 1));
	scene->addModel(BasicModels::basicCube("assets/textures/brick.png", 2));
	//scene->addModel(new Model("3D triangle1", createTriangle()[0]));
	//scene->addModel(new Model("3D triangle2", createTriangle()[0]));

	materialWidget = new ScenePropertiesWidget(scene);
}

ApplicationController::~ApplicationController()
{
	delete scene;
}

void ApplicationController::save()
{
}

void ApplicationController::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();
}
