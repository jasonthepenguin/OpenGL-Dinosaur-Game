#include "Save_Command.h"
#include "Save_Command.h"

Save_Command::Save_Command(Menu_Manager& menuManager) : m_MenuManager(menuManager)
{
}



Player* Save_Command::getPlayerData() const
{
	return m_PlayerData.get();
}



void Save_Command::setPlayerData(Player* tempPlayer)
{
	m_PlayerData.reset(tempPlayer);
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



void Save_Command::displaySaveData()
{
	if (ImGui::Begin("Save Game"))
	{
		for (int i = 0; i < 3; ++i)
		{
			ImGui::Text(("Save Slot " + std::to_string(i + 1)).c_str());

			Player* playerData = m_PlayerData.get();
			if (playerData != nullptr)
			{
				ImGui::Text(("Name: " + playerData->getPlayerName()).c_str());
				ImGui::Text(("Score: " + std::to_string(playerData->getPlayerScore())).c_str());
				ImGui::Text(("Save Date: " + playerData->getSaveDate()).c_str());
			}
		}
		ImGui::End();
	}
}



void Save_Command::saveGame(int slotNumber)
{
	if (m_PlayerData != nullptr)
	{
		std::string fileName = generateFileName(slotNumber);

		std::ofstream m_SaveFile(fileName);

		if (!m_SaveFile)
		{
			std::cerr << "Warning: Unable to open saved game file." << std::endl;
			return;
		}

		// Current date/time based on the current system
		time_t now = time(0);
		tm* ltm = localtime(&now);

		m_SaveFile << m_PlayerData->getPlayerName() << " ";
		glm::vec3 playerLocation = m_PlayerData->getPlayerLocation();
		m_SaveFile << playerLocation.x << " " << playerLocation.y << " " << playerLocation.z << " ";
		m_SaveFile << m_PlayerData->getPlayerSpeed() << " ";
		m_SaveFile << m_PlayerData->getPlayerScore() << " ";
		m_SaveFile << 1 + ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << std::endl;
		m_SaveFile.close();

		std::cout << "Game successfully saved to " << fileName << std::endl;
	}
}



void Save_Command::executeTask()
{
	displaySaveData();

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
		std::shared_ptr<Back_Command> backCommand = std::make_shared<Back_Command>();
		backCommand->executeTask();
	}
}

