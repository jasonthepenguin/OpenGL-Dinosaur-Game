#include "Back_Command.h"

Back_Command::Back_Command()
{

}

Back_Command::Back_Command(Menu_Manager& menuManager) : m_MenuManager(menuManager) {}


void Back_Command::goBack()
{
	menuManager.popMenu();
}


// Go back to the previous menu
void Back_Command::executeTask()
{
	goBack();
}