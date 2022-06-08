#pragma once
#include <glm/glm.hpp>

#include "ApplicationController.h"
#include "control/Window.h"
#include "control/Camera.h"


class Editor
{
public:
	Editor(int w, int h);
	void run();

	Window* getWindow() { return window; }
	Camera* getCamera() { return camera; }
private:

	Window* window;
	Camera* camera;
	ApplicationController* application;
	GLfloat lastX = 0, lastY = 0, xChange = 0, yChange = 0;
	bool mouseFirstMoved = true, mouseLeftClicked = false, mouseRightClicked = false;

	void close();
	void createInput();
};

class EditorData
{
public:
	static glm::mat4 getProjectionMatrix()
	{
		return editor->getWindow()->getProjectionMatrix();
	}
	static glm::mat4 getViewMatrix()
	{
		return editor->getCamera()->getViewMatrix();
	}
	static glm::vec3 getViewPosition()
	{
		return editor->getCamera()->getPos();
	}
	static void create(Editor* e)
	{
		editor = e;
	}
private:
	static Editor* editor;
};