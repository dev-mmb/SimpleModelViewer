#pragma once
#include <glew.h>
#include <glfw3.h>

#include <unordered_map>
#include <vector>
#include <functional>

#include <glm/mat4x4.hpp>

#include "InputActions.h"


class Window
{
public:
	Window(const GLint w, const GLint h);
	~Window();

	bool hasInitializedSuccessfully() const { return initializedSuccessfully;  }

	GLfloat getBufferWidth() const { return (GLfloat)bWidth; }
	GLfloat getBufferHeight() const { return (GLfloat)bHeight; }
	glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
	glm::vec2 getMousePos() const { return mousePos;  }

	bool shouldClose() const { return glfwWindowShouldClose(window); }

	void swapBuffers() { glfwSwapBuffers(window); }

	int subscribe(Input::Action key, std::function<void(const Window&, int, int, float)> c)
	{
		return Window::callbacks[key].add(c);
	}
	void unsubscribe(Input::Action key, int index)
	{
		Window::callbacks[key].remove(index);
	}
	void close() { glfwSetWindowShouldClose(window, true); }

	void update();

	void setFov(float fov)
	{
		this->fov = fov;
		if (this->fov < 1) this->fov = 1;
		if (this->fov > 179) this->fov = 179;
		calculateProjectionMatrix();
	}
	float getFov() const
	{
		return fov;
	}
	
private:
	static Window* self;
	static glm::vec2 mousePos;
	static bool keys[1024];
	static float dt;
	static float lastTime;

	GLint bWidth, bHeight, width, height;
	glm::mat4 projectionMatrix;
	float fov = 45.0f;
	bool initializedSuccessfully = false;
	GLFWwindow* window;

	class CallbackList
	{
	public:
		int add(std::function<void(const Window&, int, int, float)>& callback);
		void remove(int index);
		void call(const Window&, const int action, const int mode, float dt) const;
	private:
		struct Callback
		{
			bool isEmpty = false;
			std::function<void(const Window&, int, int, float)> func;
		};
		std::vector<Callback> callbacks;
	};

	void calculateProjectionMatrix();

	static std::unordered_map<Input::Action, CallbackList> callbacks;
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow* window, int key, int scancode, int action);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

