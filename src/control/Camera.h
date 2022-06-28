#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glew.h>

class Camera
{
public:
	Camera(glm::vec3 initialPos, glm::vec3 up, GLfloat movementSpeed, int viewPortWidht, int viewPortHeight);

	void rotate(float xChange, float yChange);

	glm::vec3 getPos() const { return pos; }
	void setPos(const glm::vec3& p);

	glm::mat4 getViewMatrix() const;
	glm::vec3 getViewDirection() const
	{
		return -glm::transpose(getViewMatrix())[2];
	}
	glm::vec3 getRightVector() const
	{
		return glm::transpose(getViewMatrix())[0];
	}
	glm::vec3 getFocus() const { return this->focus; }
	void setFocus(const glm::vec3& f);

	void zoomIn() { this->zoom += 0.01f; calculateViewMatrix(); }
	void zoomOut() { this->zoom -= 0.01f; calculateViewMatrix();  }

private:
	glm::vec3 pos;
	glm::vec3 worldUp;
	float zoom = 1;
	glm::vec3 focus = glm::vec3(0, 0, 0);
	glm::mat4 viewMatrix;
	int viewPortW, viewPortH;

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	void calculateViewMatrix();
};

