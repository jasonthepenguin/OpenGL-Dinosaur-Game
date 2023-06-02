#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include "Player.h" 
#include "Menu_Command.h"
#include "Back_Command.h"
class Load_Command : public Menu_Command
{
public:
	Load_Command();
	Load_Command(std::shared_ptr<Back_Command> back_button);
   ~Load_Command() ;

	std::string selectLoadFile();
	Player loadSavedData(int saveNumber);


	void displayLoadGameDialog();
	void executeTask() override;

private:

	// Helper functions for data extraction and validation
	std::string extractString(std::istringstream& iss);
	glm::vec3 extractVec3(std::istringstream& iss);
	float extractFloat(std::istringstream& iss);
	int extractInt(std::istringstream& iss);



	std::array<std::string, 3>	  m_SavedGames;
	std::shared_ptr<Back_Command> m_BackButton;

	std::unique_ptr<Player> m_Player;
};
