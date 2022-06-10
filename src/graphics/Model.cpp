#include "Model.h"

#include <glm/ext/matrix_transform.hpp>

#include "uniforms/Uniform1f.h"
#include <iostream>

const float toRadians = 3.14159265f / 180.f;

Model::Model(const std::string& name, const std::string& modelFileName)
{
	this->name = name;
	const aiScene* scene = importer.ReadFile(modelFileName.c_str(), 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		std::cout << "could not load scene: " << modelFileName << ",\nError: " << importer.GetErrorString() << "\n";
		return;
	}

	loadNode(scene->mRootNode, scene);
	loadTextures(scene);
}

Model::Model(const std::string& name, Mesh* m)
{
	this->name = name;
	this->meshes.push_back(m);
	this->textures.push_back(new Texture("assets/textures/brick.png"));
	this->textures[0]->load();
	this->textureIndexes.push_back(0);
}

Model::~Model()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i]->clear();
		delete meshes[i];
		meshes[i] = nullptr;
	}
	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i]->clear();
		delete textures[i];
		textures[i] = nullptr;
	}
	meshes.clear();
	textures.clear();
	textureIndexes.clear();
}

void Model::render(Shader* shader)
{
	shader->bind();
	glm::mat4 model(1.0f);

	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x * toRadians, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y * toRadians, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z * toRadians, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);

	shader->setModel(model);

	for (size_t i = 0; i < meshes.size(); i++)
	{
		unsigned int index = textureIndexes[i];
		if (index < textures.size() && textures[index])
			textures[index]->use();
		meshes[i]->render();
	}

	shader->unBind();
}

void Model::loadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z });
		}
		else
		{
			vertices.insert(vertices.end(), { 0, 0, 0 });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto m = new Mesh();
	m->create(&vertices[0], &indices[0], vertices.size(), indices.size());
	this->meshes.push_back(m);
	textureIndexes.push_back(mesh->mMaterialIndex);
}

void Model::loadTextures(const aiScene* scene)
{
	textures.resize(scene->mNumMaterials);
	for (size_t i = 0; i  < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];
		textures[i] = nullptr;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				const size_t idx = std::string(path.data).rfind('\\');
				std::string fileName = std::string(path.data).substr(idx + 1);

				std::string texPath = "textures/" + fileName;

				textures[i] = new Texture(texPath);

				if (!textures[i]->load())
				{
					delete textures[i];
					textures[i] = nullptr;
				}
			}
		}

		if (!textures[i])
		{
			textures[i] = new Texture("/assets/textures/missing.png");
		}
	}
}
