#pragma once




#include <string>
#include <memory>
#include <unordered_map>



#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "Menu.h"
#include "Menu_Manager.h"
#include "Menu_Command.h"
#include "Load_Command.h"
#include "Quit_Command.h"
#include "Save_Command.h"
#include "Resume_Command.h"
#include "CustomerSupport_Command.h"



class Pause_Menu : public Menu
{

	public:

		Pause_Menu();

		void generate() override;


		void setMenuCommand(int option, std::shared_ptr<Menu_Command> commandList);



	private:
		std::unordered_map<std::string, std::shared_ptr<Menu_Command>> m_MenuOption;

		std::shared_ptr<Menu_Manager>  menuManager;
		std::shared_ptr<Menu_Command>  loadCommand;
		std::shared_ptr<Menu_Command>  saveCommand;
		std::shared_ptr<Menu_Command>  quitCommand;
		std::shared_ptr<Menu_Command>  customerSupportCommand;
};