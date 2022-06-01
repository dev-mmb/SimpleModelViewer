#pragma once
#include <glfw3.h>

namespace Input
{
	enum class Action : int
	{
		NONE = -1,
		MOUSE_MOVEMENT = -2,
		MOUSE_WHEEL_UP = -3,
		MOUSE_WHEEL_DOWN = -4,

		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		ESCAPE = GLFW_KEY_ESCAPE,
		MOUSE_CLICK_LEFT = GLFW_MOUSE_BUTTON_LEFT
	};

	Action convertFromGlfw(int keys);
}
