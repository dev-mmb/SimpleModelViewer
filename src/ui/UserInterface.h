#pragma once

#include "imgui/imgui.h"

#include <vector>

#include "Widget.h"



class Window;

class UserInterface
{
public:
	UserInterface() {}

	void init(Window& window);
	void destroy();

	void preRender();
	void render();

	int addComponent(Widget* component);
	void removeComponent(int i);

private:
	std::vector<Widget*> components;
};

