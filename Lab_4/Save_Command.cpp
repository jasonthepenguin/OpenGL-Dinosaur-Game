#include "Save_Command.h"


Save_Command::Save_Command() : 
	m_PlayerData(nullptr)
{

}


Save_Command::~Save_Command()
{

}


const Player* Save_Command::getPlayerData() const			 
{ 
	return m_PlayerData;       
}


void Save_Command::setPlayerData(Player* tempPlayer)
{ 
	m_PlayerData = tempPlayer; 
}



void Save_Command::saveGame()
{
	if (!m_PlayerData) 
	{
		std::cerr << "Warning: No player data available to be saved." << std::endl;
		
		return;
	}


	std::ofstream saveFile("SaveGame.txt");

	if (!saveFile) 
	{
		std::cerr << "Warning: Unable to open save game file " << std::endl;
		
		return;
	}


	saveFile << m_PlayerData->getPlayerName() << '\n';


	const glm::vec3& location = m_PlayerData->getPlayerLocation();
	saveFile << location.x << ' ' << location.y << ' ' << location.z << '\n';

	saveFile << m_PlayerData->getPlayerSpeed() << std::endl;
	saveFile << m_PlayerData->getPlayerScore() << std::endl;


	const glm::vec3& m_PlayerCamera = m_PlayerData->getPlayerCamera().getCameraLocation();

	saveFile << m_PlayerCamera.x << ' ' << m_PlayerCamera.y << ' ' << m_PlayerCamera.z << '\n';

	saveFile.close();
}


void Save_Command::executeTask() 
{
	if (ImGui::Button("Save")) 
	{
		std::cout << "Saving game state..." << std::endl;

		saveGame();
	}
}