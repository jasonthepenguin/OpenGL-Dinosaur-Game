#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Menu_Command.h"
#include "Load_Command.h"
#include "CustomerSupport_Command.h"
#include "Save_Command.h"
#include "Quit_Command.h"

class Pause_Menu
{
public:
	Pause_Menu();
   ~Pause_Menu();

	void generate();
	void displayMenu();
	void setMenuCommand(const std::string& optionName, std::shared_ptr<Menu_Command> commandList);
	void addCommand(std::shared_ptr<Menu_Command> command);
	std::string getButtName() const;
	void invokeCommand(const std::string& optionName);

private:
	std::unordered_map<std::string, std::shared_ptr<Menu_Command>> m_MenuOption;
	std::vector<std::shared_ptr<Menu_Command>> m_MenuCommands;
};