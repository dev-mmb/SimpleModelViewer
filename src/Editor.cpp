#include "Editor.h"

#include <iostream>

#include "ui/ExampleUI.h"

Editor* EditorData::editor;

Editor::Editor(int w, int h)
{
	this->camera = new Camera(glm::vec3(0, 0, -5), glm::vec3(0, 1, 0), 10, w, h);
	this->window = new Window(w, h);
	EditorData::create(this);
	Widget::setUserInterface(window->getUserInterface());
	this->application = new ApplicationController();
	createInput();
}

void Editor::run()
{
	const auto ui = new ExampleUI();

	while(!window->shouldClose())
	{
		window->update();
		window->getUserInterface()->preRender();
		application->render();
		window->getUserInterface()->render();
		window->swapBuffers();
	}
	window->getUserInterface()->destroy();
	delete window;
	delete application;
	delete camera;
	delete ui;
}

void Editor::close()
{
	window->close();
}

void Editor::createInput()
{
	window->subscribe(Input::Action::MOUSE_MOVEMENT, [this](const Window& w, int action, int mods, float dt)
		{
			if (mouseLeftClicked || mouseRightClicked)
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
				if (mouseLeftClicked)
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
			//this->window->setFov(this->window->getFov() - 1);
			this->camera->zoomOut();
		});
	window->subscribe(Input::Action::MOUSE_WHEEL_DOWN, [this](const Window& w, int action, int mods, float dt)
		{
			//this->window->setFov(this->window->getFov() + 1);
			this->camera->zoomIn();
		});
}