#include "Pause_Menu.h"


Pause_Menu::Pause_Menu()
{
	m_MenuOption["customerSupport"] = std::make_shared<CustomerSupport_Command>();
	m_MenuOption["save"] = std::make_shared<Save_Command>();
	m_MenuOption["load"] = std::make_shared<Load_Command>();
	m_MenuOption["quit"] = std::make_shared<Quit_Command>();

	addCommand(std::make_shared<Save_Command>());
	addCommand(std::make_shared<Load_Command>());
	addCommand(std::make_shared<CustomerSupport_Command>());
	addCommand(std::make_shared<Quit_Command>());
}

Pause_Menu::~Pause_Menu() {}

void Pause_Menu::setMenuCommand(const std::string& optionName, std::shared_ptr<Menu_Command> command)
{
	m_MenuOption[optionName] = command;
}


void Pause_Menu::invokeCommand(const std::string& optionName)
{
	if (m_MenuOption.find(optionName) != m_MenuOption.end())
	{
		m_MenuOption[optionName]->executeTask();
	}
	else
	{
		// Handle the case where the optionName does not exist in the map.
	}
}



void Pause_Menu::generate()
{
	displayMenu();
}

void Pause_Menu::addCommand(std::shared_ptr<Menu_Command> command)
{
	m_MenuCommands.push_back(command);
}


void Pause_Menu::displayMenu()
{
	if (ImGui::Begin("Menu"))
	{
		for (const auto& option : m_MenuOption)
		{
			if (ImGui::Button(option.first.c_str()))
			{
				option.second->executeTask();
			}
		}
	}
	ImGui::End();
}

