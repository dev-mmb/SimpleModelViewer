#include "Window.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <unordered_map>
#include <iostream>

std::unordered_map<Input::Action, Window::CallbackList> Window::callbacks;
Window* Window::self;
glm::vec2 Window::mousePos;
bool Window::keys[1024];
float Window::dt = 0;
float Window::lastTime = 0;

Window::Window(const GLint w, const GLint h)
	:  bWidth(0), bHeight(0), width(w), height(h), projectionMatrix(glm::mat4())
{

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize\n";
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(width, height, "title", NULL, NULL);
	if (!window)
	{
		std::cout << "Could not make window\n";
		glfwTerminate();
		return;
	}
	glfwGetFramebufferSize(window, &bWidth, &bHeight);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init failed";
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);

	glViewport(0, 0, bWidth, bHeight);

	calculateProjectionMatrix();

	// set callbacks
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);

	subscribe(Input::Action::ESCAPE, [this](const Window& w, int action, int mods, float dt) {
		if (action == GLFW_PRESS)
		{

			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});

	initializedSuccessfully = true;
	self = this;
}

Window::~Window()
{}

void Window::calculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(glm::radians(fov), (GLfloat)bWidth / (GLfloat)bHeight, 0.1f, 100.0f);
}

void Window::update()
{
	const GLfloat now = (GLfloat)glfwGetTime();
	dt = now - lastTime;
	lastTime = now;
	glfwPollEvents();
}

int Window::CallbackList::add(std::function<void(const Window&, int, int, float)>& callback)
{
	for (size_t i = 0; i < callbacks.size(); i++)
	{
		if (callbacks[i].isEmpty)
		{
			callbacks[i].func = callback;
			callbacks[i].isEmpty = false;
			return i;
		}
	}
	callbacks.push_back({ false, callback });
	return callbacks.size() - 1;
}

void Window::CallbackList::remove(int index)
{
	callbacks[index].isEmpty = true;
}

void Window::CallbackList::call(const Window& window, const int action, const int mode, float dt) const
{
	for (size_t i = 0; i < callbacks.size(); i++)
	{
		if (callbacks[i].isEmpty == false)
		{
			callbacks[i].func(window, action, mode, dt);
		}
	}
}



void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
		Input::Action a = Input::convertFromGlfw(key);
		callbacks[a].call(*self, action, mods, dt);
	}
}

void Window::mouseCallback(GLFWwindow* window, double x, double y)
{
	mousePos.x = (float)x;
	mousePos.y = (float)y;
	callbacks[Input::Action::MOUSE_MOVEMENT].call(*self, 0, 0, dt);
}

void Window::mouseButtonCallback(GLFWwindow* window, int key, int scancode, int action)
{
	// save the old state
	bool isClicked = keys[key];
	// get wether this is a press or a release depending on the old state
	int a = (isClicked) ? GLFW_RELEASE : GLFW_PRESS;
	// set the key to true so we can get the correct event
	keys[key] = true;
	Input::Action input = Input::convertFromGlfw(key);
	// restore the old state
	keys[key] = !isClicked;
	callbacks[input].call(*self, a, 0, dt);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::Action action = (yoffset > 0) ? Input::Action::MOUSE_WHEEL_UP : Input::Action::MOUSE_WHEEL_DOWN;
	callbacks[action].call(*self, 0, 0, dt);
}


