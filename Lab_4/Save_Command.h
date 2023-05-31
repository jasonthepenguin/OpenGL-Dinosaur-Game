#pragma once


#include <ctime>
#include <fstream>
#include <iostream>


#include "imgui.h"
#include "Player.h"
#include "Menu_Command.h"
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

class Save_Command : public Menu_Command
{
public:

	Save_Command();
	~Save_Command();
	const Player* getPlayerData() const;
	void setPlayerData(Player* tempPlayer);
	void saveGame(int slotNumber);
	virtual void executeTask() override;


private:

	std::string generateFileName(int saveNumber);
	Back_Command m_BackCommand;
	Player* m_PlayerData;
};