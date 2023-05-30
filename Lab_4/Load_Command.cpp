#include "Load_Command.h"

Load_Command::Load_Command()
{

}

Load_Command::~Load_Command()
{

}



void Load_Command::loadSavedGame(Player& playerData)
{
	std::ifstream playerSaveFile("savedGame.txt");
	
	if (!playerSaveFile)
	{
		std::cerr << "Warning: Unable to open saved game file." << std::endl;
		return;
	}


	std::string m_ReadLine;

	while (std::getline(playerSaveFile, m_ReadLine))
	{
		std::istringstream m_PlayerData(m_ReadLine);

		std::string playerName   = extractString(m_PlayerData);
		glm::vec3 playerLocation = extractVec3(m_PlayerData);
		float playerSpeed	     = extractFloat(m_PlayerData);
		int playerScore			 = extractInt(m_PlayerData);

		playerData.setPlayerName(playerName);
		playerData.setPlayerLocation(playerLocation);
		playerData.setPlayerSpeed(playerSpeed);
		playerData.setPlayerScore(playerScore);
	}
	playerSaveFile.close();

	std::cout << "Game successfully loaded from the savedGame.txt file" << std::endl;
}




std::string Load_Command::extractString(std::istringstream& m_PlayerData)
{
	std::string value;
	m_PlayerData >> value;

	return value;
}


glm::vec3 Load_Command::extractVec3(std::istringstream& m_PlayerData)
{
	glm::vec3 playerData;
	m_PlayerData >> playerData.x >> playerData.y >> playerData.z;
	
	return playerData;
}


float Load_Command::extractFloat(std::istringstream& m_PlayerData)
{
	float floatValue;
	m_PlayerData >> floatValue;


	return floatValue;
}



int Load_Command::extractInt(std::istringstream& m_PlayerData)
{
	int integerValue;
	m_PlayerData >> integerValue;
	
	
	return integerValue;
}