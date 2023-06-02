#include "Menu_Manager.h"

void Menu_Manager::handleInput(GLFWwindow* window)
{
	// Check if the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (!m_CommandStack.empty())
		{
			// If the command stack is not empty, remove the top command and return
			m_CommandStack.pop_back();
			return;
		}
		else
		{
			std::shared_ptr<Menu_Command> pauseCommand = std::make_shared<Pause_Command>();
			m_CommandStack.push_back(pauseCommand);
		}
	}
	else
	{
		// Handle other input events or game logic here
	}
}



void Menu_Manager::generateMenu()
{
	if (!m_CommandStack.empty())
	{
		// Generate and execute the top command in the stack
		std::shared_ptr<Menu_Command> topCommand = m_CommandStack.back();
		topCommand->executeTask();
	}
}



void Menu_Manager::pushCommand(std::shared_ptr<Menu_Command> command)
{
	m_CommandStack.push_back(command);
}



void Menu_Manager::popMenu()
{
	if (!m_CommandStack.empty())
	{
		m_CommandStack.pop_back();
	}
}