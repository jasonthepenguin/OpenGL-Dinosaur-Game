#include "Load_Command.h"

Load_Command::Load_Command(std::shared_ptr<Back_Command> back_button)
	: m_BackButton(std::move(back_button))
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
		for (int i = 0; i < 3; ++i)
		{
			if (ImGui::Button(("Load " + std::to_string(i + 1)).c_str()))
			{
				Player playerData;
				loadSavedGame(i + 1);
				std::cout << "Loaded game: " << playerData.getPlayerName() << ", Score: " << playerData.getPlayerScore() << std::endl;
			}
			ImGui::Text(m_SavedGames[i].c_str());
		}

		if (ImGui::Button("Back"))
		{
			m_BackButton->executeTask(); // Go back to the main menu
		}

		ImGui::End();
	}
}



Player Load_Command::loadSavedGame(int saveNumber) const
{
	Player playerData; // Create a Player object to hold the loaded game data
	std::string fileName = m_SavedGames[saveNumber - 1];
	std::ifstream playerSaveFile(fileName);

	if (!playerSaveFile)
	{
		std::cerr << "Warning: Unable to open saved game file: " << fileName << std::endl;
		return playerData;
	}

	playerSaveFile >> playerData.getPlayerName();
	playerSaveFile >> playerData.getPlayerLocation().x;
	playerSaveFile >> playerData.getPlayerLocation().y;
	playerSaveFile >> playerData.getPlayerLocation().z;
	playerSaveFile >> playerData.getPlayerSpeed();
	playerSaveFile >> playerData.getPlayerScore();
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
	loadSavedGame();
}