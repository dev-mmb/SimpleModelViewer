#include "Editor.h"

#include <iostream>

Editor* EditorData::editor;

Editor::Editor(int w, int h)
{
	this->camera = new Camera(glm::vec3(0, 0, -5), glm::vec3(0, 1, 0), 0, 0, 10, w, h);
	this->window = new Window(w, h);
	EditorData::create(this);
	this->application = new ApplicationController();
	createInput();
}

void Editor::run()
{
	while(!window->shouldClose())
	{
		window->update();
		application->render();
		window->swapBuffers();
	}
	delete window;
	delete application;
	delete camera;
}

void Editor::close()
{
	window->close();
}

void Editor::createInput()
{
	window->subscribe(Input::Action::MOUSE_MOVEMENT, [this](const Window& w, int action, int mods, float dt)
		{
			if (mouseLeftClicked)
			{
				glm::vec2 mousePos = w.getMousePos();
				if (mouseFirstMoved)
				{
					lastX = mousePos.x;
					lastY = mousePos.y;
					mouseFirstMoved = false;
				}
				xChange = mousePos.x - lastX;
				yChange = lastY - mousePos.y;
				lastX = mousePos.x;
				lastY = mousePos.y;
				camera->rotate(-xChange, yChange);
			}
		});
	window->subscribe(Input::Action::MOUSE_CLICK_LEFT, [this](const Window& w, int action, int mods, float dt)
		{
			if (action == GLFW_PRESS)
			{
				mouseLeftClicked = true;
				mouseFirstMoved = true;
			}
			else
			{
				mouseLeftClicked = false;
				mouseFirstMoved = true;
			}
		});
	window->subscribe(Input::Action::MOUSE_WHEEL_UP, [this](const Window& w, int action, int mods, float dt)
		{
			this->window->setFov(this->window->getFov() - 1);
		});
	window->subscribe(Input::Action::MOUSE_WHEEL_DOWN, [this](const Window& w, int action, int mods, float dt)
		{
			this->window->setFov(this->window->getFov() + 1);
		});
}