#include "StaticMesh.h"

#include <glm/ext/matrix_transform.hpp>

#include "uniforms/Uniform1f.h"

const float toRadians = 3.14159265f / 180.f;

StaticMesh::StaticMesh(const std::string& vshader, const std::string& fshader, Mesh* mesh)
{
	createNewShader(vshader, fshader);
	this->addMesh(mesh);
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

void StaticMesh::createNewShader(const std::string& vshader, const std::string& fshader)
{
	if (shader != nullptr)
	{
		delete shader;
	}
	this->shader = new Shader(vshader, fshader);

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
