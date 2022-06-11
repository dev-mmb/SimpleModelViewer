#include "Mesh.h"

Mesh::Mesh()
	: VAO(0), VBO(0), IBO(0), indexCount(0)
{}

Mesh::~Mesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

void Mesh::create(GLfloat* vertices, unsigned int* indices, unsigned int vCount, unsigned int iCount)
{
	indexCount = iCount;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	{
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * iCount, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vCount, vertices, GL_STATIC_DRAW);

		int stride = sizeof(vertices[0]) * 8;
		int textureOffset = sizeof(vertices[0]) * 3;
		int normalOffset = sizeof(vertices[0]) * 5;

		// set vertex offset
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);
		// set texture offset
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)textureOffset);
		glEnableVertexAttribArray(1);
		// set normal location
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffset);
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render() const
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}