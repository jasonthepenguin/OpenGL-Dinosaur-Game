#pragma once



/***************************************************************************************************************
 * @brief : SaveCommand
 * @brief :
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Menu_Command.h"
#include "Player.h"
#include "Menu_Manager.h"

class Save_Command : public Menu_Command
{
public:
	Save_Command(Menu_Manager& menuManager);
	Player* getPlayerData() const;
	void setPlayerData(Player* tempPlayer);
	void executeTask() override;

private:
	std::string generateFileName(int saveNumber);
	void displaySaveData();
	void saveGame(int slotNumber);

	Menu_Manager& m_MenuManager;
	std::unique_ptr<Player> m_PlayerData;
};
