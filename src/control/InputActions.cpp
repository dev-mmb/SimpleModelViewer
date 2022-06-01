#include "InputActions.h"

#include <glfw3.h>
#include <iostream>

Input::Action Input::convertFromGlfw(int keys)
{
	return static_cast<Input::Action>(keys);
}
