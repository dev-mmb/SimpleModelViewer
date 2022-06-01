#pragma once
#include <imgui/imgui.h>

#include "Widget.h"

class ExampleUI : public Widget
{
public:
	ExampleUI() : Widget(userInterface)
	{}

	bool show_demo_window = true;

	void render() override
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
};
