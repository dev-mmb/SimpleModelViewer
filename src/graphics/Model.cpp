#include "Model.h"

#include <glm/ext/matrix_transform.hpp>

#include "uniforms/Uniform1f.h"
#include <iostream>
#include <assimp/postprocess.h>

#include "imgui/imgui.h"
#include "L2DFileDialog/L2DFileDialog.h"
#include "uniforms/UniformSampler2D.h"

const float toRadians = 3.14159265f / 180.f;
const std::string Model::AMBIENT_NAME = "ambient";
const std::string Model::DIFFUSE_NAME = "diffuse";
const std::string Model::SPECULAR_NAME = "specular";
const std::string Model::SHINE_NAME = "shine";

Model::Model(const std::string& name, const std::string& modelFileName)
{
	this->name = name; this->filePath = modelFileName;
	const aiScene* scene = importer.ReadFile(modelFileName.c_str(), 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		std::cout << "could not load scene: " << modelFileName << ",\nError: " << importer.GetErrorString() << "\n";
		return;
	}

	loadNode(scene->mRootNode, scene);
}

Model::Model(const std::string& name, Mesh* m, const std::string& texturePath)
{
	this->name = name;
	auto pair = std::make_pair(m, std::vector<Texture*>());
	auto tex = new Texture(texturePath, Model::DIFFUSE_NAME);
	tex->load();
	pair.second.push_back(tex);
	tex = new Texture(texturePath, Model::SPECULAR_NAME);
	tex->load();
	pair.second.push_back(tex);
	this->meshes.push_back(pair);
	this->allTextures.insert(allTextures.end(), pair.second.begin(), pair.second.end());
}

Model::~Model()
{
	for (auto& mesh : meshes)
	{
		delete mesh.first;
		mesh.first = nullptr;

		for (auto& j : mesh.second)
		{
			j->clear();
			delete j;
			j = nullptr;
		}
		mesh.second.clear();
	}
	meshes.clear();
	allTextures.clear();
}

void Model::render(Shader* shader)
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x * toRadians, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y * toRadians, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z * toRadians, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);

	shader->getMaterial("material").setUniform<Uniform1f, float>(SHINE_NAME, shine);

	shader->setModel(model);

	shader->bind();

	for (size_t i = 0; i < meshes.size(); i++)
	{
		std::vector<Texture*>& textures = meshes[i].second;
		for (Texture* t : textures)
		{
			shader->getMaterial("material").setUniform<UniformSampler2D, Texture*>(t->getType(), t);
			// increment the texture unit so it is bound correctly
			Texture::incrementTextureIndex();
		}
		meshes[i].first->render();
		Texture::resetTextureIndex();
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
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
		}
		else
		{
			vertices.insert(vertices.end(), { 0, 0 });
		}
		vertices.insert(vertices.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
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
	auto vector = std::vector<Texture*>();

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	vector = loadMaterialTextures(material, aiTextureType_DIFFUSE, Model::DIFFUSE_NAME);
	std::vector<Texture*> textures = loadMaterialTextures(material, aiTextureType_SPECULAR, Model::SPECULAR_NAME);
	vector.insert(vector.end(), textures.begin(), textures.end());
	// save the textures for the ui
	allTextures.insert(allTextures.end(), vector.begin(), vector.end());

	auto pair = std::make_pair(m, vector);
	this->meshes.push_back(pair);
}


std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		const size_t idx = std::string(str.data).rfind('\\');
		std::string fileName = std::string(str.data).substr(idx + 1);

		std::string texPath = getFilePathWithoutFileName() + fileName;

		auto texture = new Texture(texPath, typeName);
		if (!texture->load())
		{
			std::cout << "could not load texture: " << texPath << "\n";
			delete texture;
			texture = new Texture("/assets/textures/missing.png", typeName);
		}
		textures.push_back(texture);
	}
	return textures;
}
