#pragma once

#include <stack>
#include <memory>
#include <GLFW/glfw3.h>
#include "Pause_Menu.h"
#include <vector>
#include "Pause_Command.h"
class Menu_Command;


class Menu_Manager
{
public:
	void handleInput(GLFWwindow* window);
	void generateMenu();
	void pushCommand(std::shared_ptr<Menu_Command> command);
	void popMenu();

private:
	std::vector<std::shared_ptr<Menu_Command>> m_CommandStack;
};

