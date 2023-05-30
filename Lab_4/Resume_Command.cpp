#include "Resume_Command.h"


void Resume_Command::executeTask()
{
	if (ImGui::Button("Resume Game"))
	{
		std::cout << "Resuming game." << std::endl;
	}
}



void Resume_Command::executeTask()
{
	// Hide the menu
	//auto& menu = Pause_Menu::getInstance();
	//menu.hideMenu();
}