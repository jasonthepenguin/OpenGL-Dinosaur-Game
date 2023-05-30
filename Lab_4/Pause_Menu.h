#pragma once

#include <memory>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



#include "Menu_Commands.h"
#include "Load_Command.h"
#include "Quit_Command.h"
#include "Save_Command.h"
#include "Resume_Command.h"
#include "CustomerSupport_Command.h"



class Pause_Menu
{
	public:
		Pause_Menu();

		void generatePauseMenu();

	private:
		std::unordered_map<std::string, std::shared_ptr<Menu_Commands>> m_MenuOption;
};