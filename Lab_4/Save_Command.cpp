#include "Save_Command.h"


Save_Command::Save_Command() : m_PlayerData(nullptr)
{

}


Save_Command::~Save_Command()
{
	if (m_PlayerData != nullptr)
	{
		delete m_PlayerData;
		m_PlayerData = nullptr;
	}
}

const Player* Save_Command::getPlayerData() const
{
	return m_PlayerData;
}


void Save_Command::setPlayerData(Player* tempPlayer)
{
	if (m_PlayerData != nullptr)
	{
		delete m_PlayerData;
		m_PlayerData = nullptr;
	}

	if (tempPlayer != nullptr)
	{
		m_PlayerData = tempPlayer;
	}
	else
	{
		m_PlayerData = new Player;
	}
}



std::string Save_Command::generateFileName(int saveNumber)
{
	switch (saveNumber)
	{
		case 1: return "saveOne.txt";
		case 2: return "saveTwo.txt";
		case 3: return "saveThree.txt";
		
		default:
			std::cerr << "Invalid slot number" << std::endl;
		return "";
	}
}



void Save_Command::saveGame(int slotNumber)
{
	if (m_PlayerData != nullptr)
	{
		std::string fileName = generateFileName(slotNumber);

		std::ofstream m_SaveFile(fileName);

		if (fileName.empty())
		{
			std::cerr << "Warning: Unable to open saved game file." << std::endl;
			return;
		}

		// current date/time based on current system
		time_t now = time(0);
		tm* ltm = localtime(&now);

		m_SaveFile << m_PlayerData->getPlayerName() << " ";
		glm::vec3 playerLocation = m_PlayerData->getPlayerLocation();
		m_SaveFile << playerLocation.x << " " << playerLocation.y << " " << playerLocation.z << " ";
		m_SaveFile << m_PlayerData->getPlayerSpeed() << " ";
		m_SaveFile << m_PlayerData->getPlayerScore() << " ";
		m_SaveFile << 1 + ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << std::endl;
		m_SaveFile.close();
		std::cout << "Game successfully saved to the " << fileName << std::endl;
	}
}



void Save_Command::executeTask()
{
	if (ImGui::Button("Save 1"))
	{
		saveGame(1);
	}
	if (ImGui::Button("Save 2"))
	{
		saveGame(2);
	}
	if (ImGui::Button("Save 3"))
	{
		saveGame(3);
	}

	if (ImGui::Button("Back"))
	{
		Back_Command m_BackCommand;
		// implement functionality to go back to main pause menu
	}
}
