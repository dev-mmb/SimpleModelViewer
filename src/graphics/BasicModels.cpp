#include "BasicModels.h"

void BasicModels::calculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices,
                             unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 norm = glm::cross(v1, v2);
		norm = glm::normalize(norm);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += norm.x; vertices[in0 + 1] += norm.y; vertices[in0 + 2] += norm.z;
		vertices[in1] += norm.x; vertices[in1 + 1] += norm.y; vertices[in1 + 2] += norm.z;
		vertices[in2] += norm.x; vertices[in2 + 1] += norm.y; vertices[in2 + 2] += norm.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		const unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}
Model* BasicModels::basicCube(const std::string& texturePath, int num)
{
	GLfloat vertices[] = {
		// x, y, z, u, v
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,	 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,	 1.0f, 1.0f,	0.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, 1.0f,	 0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,	0.0f, 0.0f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		2, 3, 6,
		3, 6, 7,
		1, 2, 6,
		1, 5, 6,
		0, 1, 5,
		0, 4, 5,
		0, 3, 7,
		0, 7, 4,
		4, 5, 6,
		4, 6, 7
	};
	Mesh* m = new Mesh();
	m->create(vertices, indices, 64, 36);
	return new Model("light" + texturePath + std::to_string(num), m, texturePath);
}

Model* BasicModels::basicTriangle()
{
	GLfloat vertices[] = {
		// x, y, z, u, v
		-1.0f, -1.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,	 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	 0.5f, 1.0f,	0.0f, 0.0f, 0.0f,
	};
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	BasicModels::calculateAverageNormals(indices, 12, vertices, 32, 8, 5);
	Mesh* m = new Mesh();
	m->create(vertices, indices, 32, 12);
	return new Model("triangle", m, "assets/textures/brick.png");
}