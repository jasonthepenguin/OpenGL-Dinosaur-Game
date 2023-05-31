#include "Pause_Menu.h"



Pause_Menu::Pause_Menu()
{
	m_MenuOption["customerSupport"] = std::make_shared<CustomerSupport_Command>();
	m_MenuOption["save"]			= std::make_shared<Save_Command>();
	m_MenuOption["load"]			= std::make_shared<Load_Command>();
	m_MenuOption["resume"]		    = std::make_shared<Resume_Command>();
	m_MenuOption["quit"]		    = std::make_shared<Quit_Command>();
}



Pause_Menu::~Pause_Menu(){}


void Pause_Menu::setMenuCommand(int option, std::shared_ptr<Menu_Command> commandList)
{
	switch (option)
	{
	case 1:
		m_MenuOption["load"] = commandList;
		break;

	case 2:
		m_MenuOption["save"] = commandList;
		break;

	case 3:
		m_MenuOption["quit"] = commandList;
		break;

	case 4:
		m_MenuOption["customerSupport"] = commandList;
		break;

	default:
		break;
	}
}


void Pause_Menu::generate()
{
	if (ImGui::Begin("Menu"))
	{
		for (const auto& command : m_MenuOption)
		{
			ImGui::Button(command.first.c_str());
		}
	}
	ImGui::End();
}




/****************
class Menu
{
public:
	virtual ~Menu() {}
	virtual void draw() = 0;
};

class MainMenu : public Menu
{
public:
	void draw() override
	{
		if (ImGui::Button("Customer Support"))
		{
			// Push Customer Support menu
		}

		if (ImGui::Button("Save"))
		{
			// Push Save menu
		}

		if (ImGui::Button("Load"))
		{
			// Push Load menu
		}

		if (ImGui::Button("Resume"))
		{
			// Resume game
		}

		if (ImGui::Button("Quit"))
		{
			// Quit application
		}
	}
};

class CustomerSupportMenu : public Menu
{
public:
	void draw() override
	{
		ImGui::Text("Customer Support Info");

		if (ImGui::Button("Back"))
		{
			// Pop this menu
		}
	}
};

// Define other menus similarly...


void SpecialKeys::pauseGame()
{
	if (!isMenuOpen)
	{
		menuManager.pushMenu(std::make_shared<MainMenu>());
		isMenuOpen = true;
	}
	else
	{
		// code to close the menu
		isMenuOpen = false;
	}
}
**/