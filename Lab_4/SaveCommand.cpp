#include "SaveCommand.h"


SaveCommand::SaveCommand()
{

}


void SaveCommand::executeTask()
{
	if (ImGui::Button("Save")) 
	{
		// Logic to save game state goes here
		std::cout << "Saving game state..." << std::endl;
	}
}




void SaveCommand::saveGame(const std::string& saveFile)
{
	std::ofstream writeSaveFile(saveFile);

	writeSaveFile << playerScore    << std::endl;
	writeSaveFile << playerLocation << std::endl;

	writeSaveFile.close();
}





#include "IPauseMenuCommand.h"
#include <iostream>

	class ResumeCommand : public PauseMenu_Commands {
	public:
		ResumeCommand() = default;

		void generate() override {
			if (ImGui::Button("Resume")) {
				// Logic to resume game goes here
				std::cout << "Resuming game..." << std::endl;
			}
		}
	};
	Here is the QuitCommand class :

		cpp
		Copy code
#include "IPauseMenuCommand.h"
#include <iostream>

		class QuitCommand : public PauseMenu_Commands {
		public:
			QuitCommand() = default;

			void generate() override {
				if (ImGui::Button("Quit")) {
					// Logic to quit game goes here
					std::cout << "Quitting game..." << std::endl;
				}
			}
	};
	Here is the KeybindingsCommand class :

		cpp
		Copy code
#include "IPauseMenuCommand.h"
#include <iostream>

		class KeybindingsCommand : public PauseMenu_Commands {
		public:
			KeybindingsCommand() = default;

			void generate() override {
				ImGui::Begin("Keybindings");
				// Display and possibly change keybindings here
				ImGui::End();
			}