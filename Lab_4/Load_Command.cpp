#include "Load_Command.h"

Load_Command::Load_Command()
	: m_BackButton(nullptr)
{
}

Load_Command::Load_Command(std::shared_ptr<Back_Command> back_button)
	: m_BackButton(back_button)
{
	m_SavedGames = { "saveOne.txt", "saveTwo.txt", "saveThree.txt" };
}

Load_Command::~Load_Command()
{

}

void Load_Command::displayLoadGameDialog()
{
	if (ImGui::Begin("Load Game"))
	{
		if (ImGui::Button("Load 1"))
		{
			Player playerData = loadSavedData(1); // Update this line
			std::cout << "Loaded game: " << playerData.getPlayerName() << std::endl;
		}
		if (ImGui::Button("Load 2"))
		{
			Player playerData = loadSavedData(2); // Update this line
			std::cout << "Loaded game: " << playerData.getPlayerName() << std::endl;
		}
		if (ImGui::Button("Load 3"))
		{
			Player playerData = loadSavedData(3); // Update this line
			std::cout << "Loaded game: " << playerData.getPlayerName() << std::endl;
		}

		if (ImGui::Button("Back"))
		{
			executeTask(); // Go back to the main menu
		}
		ImGui::End();
	}
}


Player Load_Command::loadSavedData(int saveNumber)
{
	Player playerData; // Create a Player object to hold the loaded game data
	std::string fileName = m_SavedGames[saveNumber - 1];
	std::ifstream playerSaveFile(fileName);

	if (!playerSaveFile)
	{
		std::cerr << "Warning: Unable to open saved game file: " << fileName << std::endl;
		return playerData;
	}

	std::string name;
	int score;
	playerSaveFile >> name;
	playerSaveFile >> score;
	playerData.setPlayerName(name);
	playerData.setPlayerScore(score);
	playerSaveFile.close();

	std::cout << "Game successfully loaded from the saved game file: " << fileName << std::endl;

	return playerData;
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


void Load_Command::executeTask()
{
	if (ImGui::Begin("Load Game")) // Added ImGui window
	{
		if (ImGui::Button("Load 1"))
		{
			loadSavedData(1);
		}
		if (ImGui::Button("Load 2"))
		{
			loadSavedData(2);
		}
		if (ImGui::Button("Load 3"))
		{
			loadSavedData(3);
		}

		if (ImGui::Button("Back"))
		{
			m_BackButton->executeTask();
		}

		ImGui::End();
	}
}
