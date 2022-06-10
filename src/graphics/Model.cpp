#include "Model.h"

#include <glm/ext/matrix_transform.hpp>

#include "uniforms/Uniform1f.h"
#include <iostream>
#include <assimp/postprocess.h>

#include "imgui/imgui.h"
#include "uniforms/UniformSampler2D.h"

const float toRadians = 3.14159265f / 180.f;
const std::string Model::AMBIENT_NAME = "ambient";
const std::string Model::DIFFUSE_NAME = "diffuse";
const std::string Model::SPECULAR_NAME = "specular";
const std::string Model::SHINE_NAME = "shine";

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
	this->diffuseMaps.push_back(new Texture("assets/textures/brick.png"));
	this->diffuseMaps[0]->load();
	this->specularMaps.push_back(new Texture("assets/textures/brick.png"));
	this->specularMaps[0]->load();
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
	for (size_t i = 0; i < diffuseMaps.size(); i++)
	{
		diffuseMaps[i]->clear();
		delete diffuseMaps[i];
		diffuseMaps[i] = nullptr;
	}
	for (size_t i = 0; i < specularMaps.size(); i++)
	{
		specularMaps[i]->clear();
		delete specularMaps[i];
		specularMaps[i] = nullptr;
	}
	meshes.clear();
	diffuseMaps.clear();
	specularMaps.clear();
	textureIndexes.clear();
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
		const unsigned int index = textureIndexes[i];
		if (index < diffuseMaps.size() && index < specularMaps.size() && diffuseMaps[index] && specularMaps[index])
		{
			shader->getMaterial("material").setUniform<UniformSampler2D, Texture*>(DIFFUSE_NAME, diffuseMaps[i]);
			shader->getMaterial("material").setUniform<UniformSampler2D, Texture*>(SPECULAR_NAME, specularMaps[i]);
		}
		meshes[i]->render();
	}

	shader->unBind();
}

void Model::renderUi()
{
	float vec[3] = { position.x, position.y, position.z };
	ImGui::DragFloat3("Position", vec, 0.01f);
	setPosition(glm::vec3{ vec[0], vec[1], vec[2] });

	vec[0] = rotation.x; vec[1] = rotation.y; vec[2] = rotation.z;
	ImGui::DragFloat3("Rotation", vec);
	setRotation(glm::vec3{ vec[0], vec[1], vec[2] });

	vec[0] = scale.x; vec[1] = scale.y; vec[2] = scale.z;
	ImGui::DragFloat3("Scale", vec, 0.01f);
	setScale(glm::vec3{ vec[0], vec[1], vec[2] });

	ImGui::BulletText("Material");
	ImGui::DragFloat(SHINE_NAME.c_str(), &shine, 0.01f);
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
	diffuseMaps.resize(scene->mNumMaterials);
	specularMaps.resize(scene->mNumMaterials);
	for (size_t i = 0; i  < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];
		diffuseMaps[i] = nullptr;
		specularMaps[i] = nullptr;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				const size_t idx = std::string(path.data).rfind('\\');
				std::string fileName = std::string(path.data).substr(idx + 1);

				std::string texPath = "textures/" + fileName;

				diffuseMaps[i] = new Texture(texPath);
				specularMaps[i] = new Texture(texPath);

				if (!diffuseMaps[i]->load() || !specularMaps[i]->load())
				{
					delete diffuseMaps[i];
					delete specularMaps[i];
					diffuseMaps[i] = nullptr;
					specularMaps[i] = nullptr;
				}
			}
		}

		if (!diffuseMaps[i] || !specularMaps[i])
		{
			diffuseMaps[i] = new Texture("/assets/textures/missing.png");
			specularMaps[i] = new Texture("/assets/textures/missing.png");
		}
	}
}
