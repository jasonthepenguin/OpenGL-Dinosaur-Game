#pragma once


#include <fstream>
#include <iostream>


#include "imgui.h"
#include "Player.h"
#include "Menu_Commands.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


/***************************************************************************************************************
 * @brief : SaveCommand
 * @brief : 
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class Save_Command : public Menu_Commands
{
    public:

		Save_Command();
		~Save_Command();
		const Player* getPlayerData() const;
		void setPlayerData(Player* tempPlayer);
		void saveGame();
		virtual void executeTask() override;


    private:

		Player* m_PlayerData;
};