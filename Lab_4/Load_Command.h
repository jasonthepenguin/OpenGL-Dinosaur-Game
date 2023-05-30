#pragma once


#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

#include "Player.h" 
#include "Menu_Commands.h"

class Load_Command : public Menu_Commands
{
public:
	Load_Command();
	~Load_Command();

	void loadSavedGame(Player& player); // Pass Player object by reference

private:
	// Helper functions for data extraction and validation
	std::string extractString(std::istringstream& iss);
	glm::vec3 extractVec3(std::istringstream& iss);
	float extractFloat(std::istringstream& iss);
	int extractInt(std::istringstream& iss);

	Player m_PlayerData;
};

