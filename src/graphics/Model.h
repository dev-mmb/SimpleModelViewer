#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "basic/Mesh.h"
#include "basic/Texture.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"


class Model
{
public:
	Model(const std::string& name, const std::string& modelFileName);
	Model(const std::string& name, Mesh* m);
	~Model();
	void render(Shader* shader);

	void addMesh(Mesh* mesh);

	void setPosition(const glm::vec3& position){ this->position = position; }
	glm::vec3 getPosition() const { return position; }
	void setRotation(const glm::vec3& rotation) { this->rotation = rotation; }
	glm::vec3 getRotation() const { return rotation; }
	void setScale(const glm::vec3& scale) { this->scale = scale; }
	glm::vec3 getScale() const { return scale; }
	std::string getname() const { return name; }

private:
	std::string name;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;
	std::vector<unsigned int> textureIndexes;
	Assimp::Importer importer;
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	void loadNode(aiNode* node, const aiScene* scene);
	void loadMesh(aiMesh* mesh, const aiScene* scene);
	void loadTextures(const aiScene* scene);
};

