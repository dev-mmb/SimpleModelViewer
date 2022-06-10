#pragma once
#include "Model.h"

namespace BasicModels
{
	void calculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices,
		unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);

	Model* basicCube(const std::string& texturePath, int num);

	Model* basicTriangle();
};