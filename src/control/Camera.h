#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glew.h>

class Camera
{
public:
	Camera(glm::vec3 initialPos, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, int viewPortWidht, int viewPortHeight);

	void moveForward(float dt);
	void moveBackwards(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void rotate(float xChange, float yChange);

	glm::vec3 getPos() const { return pos; }

	glm::mat4 getViewMatrix() const;
	glm::vec3 getViewDirection() const
	{
		return -glm::transpose(getViewMatrix())[2];
	}
	glm::vec3 getRightVector() const
	{
		return glm::transpose(getViewMatrix())[0];
	}
private:
	glm::vec3 pos;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 worldUp;
	glm::vec3 focus = glm::vec3(0, 0, 0);
	glm::mat4 viewMatrix;
	int viewPortW, viewPortH;

	GLfloat movementSpeed;
	GLfloat turnSpeed;
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	void calculateViewMatrix();
};

