#pragma once


#include <GLFW/glfw3.h>


#include "imgui.h"
#include "Menu_Commands.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



class Quit_Command : public Menu_Commands
{
public:
	Quit_Command() = default;
	~Quit_Command();
	void executeTask() override;
};

