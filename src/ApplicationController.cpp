#include "ApplicationController.h"
#include "Editor.h"

const float toRadians = 3.14159265f / 180.f;

ApplicationController::ApplicationController() 
{
	brickTexture = new Texture("assets/textures/brick.png");
	brickTexture->load();

	createTriangle();

	shader = new Shader(vertexShaderSource, fragmentShaderSource);

	shader->addMaterial("material");
	shader->addMaterial("directionalLight");
	shader->getMaterial("material").setUniform<Uniform1f, float>("specularIntensity", 5);
	shader->getMaterial("material").setUniform<Uniform1f, float>("shine", 32);

	shader->getMaterial("directionalLight").setUniform<Uniform1f, float>("diffuseIntensity", 3);
	shader->getMaterial("directionalLight").setUniform<Uniform1f, float>("ambientIntensity", 3);
	shader->getMaterial("directionalLight").setUniform<Uniform3f, glm::vec3>("direction", glm::vec3(2, -1, -2));
	shader->getMaterial("directionalLight").setUniform<Uniform3f, glm::vec3>("color", glm::vec3(0.4f, 0.3f, 0.0f));
	shader->compile();
}

ApplicationController::~ApplicationController()
{
	for (Mesh* m : meshes)
	{
		m->clear();
		delete m;
	}
	delete shader;

}

void ApplicationController::save()
{
}

int xrot = 0;
void ApplicationController::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();

	xrot++;
	if (xrot > 360) xrot = 0;

	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(0.f, 0, 0.f));
	m = glm::rotate(m, 0 * toRadians, glm::vec3(0, 1, 0));
	m = glm::scale(m, glm::vec3(2, 2, 2.f));

	shader->setModel(m);

	brickTexture->use();

	for (const Mesh* mesh : meshes)
	{
		mesh->render();
	}

	shader->unBind();
}
