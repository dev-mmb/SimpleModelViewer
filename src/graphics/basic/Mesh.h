#pragma once

#include <glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void create(GLfloat* vertices, unsigned int* indices, unsigned int vCount, unsigned int iCount);
	void render() const;
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

