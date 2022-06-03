#include "StaticMesh.h"

#include <glm/ext/matrix_transform.hpp>

const float toRadians = 3.14159265f / 180.f;

StaticMesh::StaticMesh(Shader* shader, Mesh* mesh)
{
	this->shader = shader; this->addMesh(mesh);
	brickTexture = new Texture("assets/textures/brick.png");
	brickTexture->load();
}

StaticMesh::~StaticMesh()
{
	for (Mesh* m : meshes)
	{
		m->clear();
		delete m;
	}
	delete shader;
}

void StaticMesh::render() const
{
	shader->bind();
	glm::mat4 model(1.0f);

	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x * toRadians, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y * toRadians, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z * toRadians, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);

	shader->setModel(model);

	brickTexture->use();

	for (const Mesh* mesh : meshes)
	{
		mesh->render();
	}
	shader->unBind();

}

void StaticMesh::renderMaterialsUi()
{
	shader->renderMaterialsUi();
}

void StaticMesh::addMesh(Mesh* mesh)
{
	this->meshes.push_back(mesh);
}
