#pragma once
#include <vector>

#include "Shader.h"
#include "basic/Mesh.h"
#include "basic/Texture.h"

class StaticMesh
{
public:
	StaticMesh(Shader* shader, Mesh* mesh);
	~StaticMesh();
	void render() const;
	void renderMaterialsUi();

	void addMesh(Mesh* mesh);

	void setPosition(const glm::vec3& position){ this->position = position; }
	glm::vec3 getPosition() const { return position; }
	void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
	glm::vec3 getRotation() const { return rotation; }
	void setScale(const glm::vec3& scale) { this->scale = scale; }
	glm::vec3 getScale() const { return scale; }

private:
	Shader* shader;
	Texture* brickTexture;

	std::vector<Mesh*> meshes;
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
};

