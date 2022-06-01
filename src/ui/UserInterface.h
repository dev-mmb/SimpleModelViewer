#pragma once

#include <vector>

#include "UserInterfaceComponent.h"

class Window;

class UserInterface
{
public:
	UserInterface() {}

	void init(Window& window);
	void destroy();

	void preRender();
	void render();

	void addComponent(UserInterfaceComponent* component);

private:
	std::vector<UserInterfaceComponent*> components;
};

