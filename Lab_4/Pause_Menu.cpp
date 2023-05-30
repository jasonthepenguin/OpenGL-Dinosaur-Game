#include "PauseMenu.h"


PauseMenu::PauseMenu()
{
	m_MenuOption["customerSupport"] = std::make_shared<CustomerSupportCommand>();
	m_MenuOption["load"] = std::make_shared<Load_Command>();
	m_MenuOption["quit"] = std::make_shared<Quit_Command>();
	m_MenuOption["resume"] = std::make_shared<Resume_Command>();
	m_MenuOption["save"] = std::make_shared<Save_Command>();
}


void PauseMenu::generatePauseMenu()
{
	if (ImGui::Begin("Menu"))
	{
		for (auto& command : m_MenuOption)
		{
			command.second->executeTask();
		}
	}
	ImGui::End();
}

