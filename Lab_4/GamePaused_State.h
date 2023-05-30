#pragma once

#include <map>
#include <memory>
#include <unordered_map>


#include "Window.h"
#include "EngGUI.h"

#include "GameState.h"
#include "Mouse_Input.h"
#include "Quit_Command.h"
#include "Load_Command.h"
#include "Save_Command.h"
#include "Menu_Commands.h"
#include "Keyboard_Input.h"
#include "Resume_Command.h"

#include "CustomerSupport_Command.h"

/***************************************************************************************************************
 * @brief : PausedGameState
 * @brief :
 *
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class GamePaused_State : public GameState
{
    public:
        GamePaused_State(std::shared_ptr<Window> window, std::shared_ptr<Keyboard_Input> keyboardInput, std::shared_ptr<Mouse_Input> mouseInput, std::shared_ptr<EngGUI> gui);
        ~GamePaused_State();

        void handlePlayerInput() override;
        void Enter() override;
        void update() override;
        void generate() override;
        void Exit() override;


    private:

		std::shared_ptr<Window>         m_window;
		std::shared_ptr<Mouse_Input>    m_mouseInput;
		std::shared_ptr<Keyboard_Input> m_keyboardInput;
		std::shared_ptr<EngGUI>         m_DisplayOptions;
		std::map<std::string, std::shared_ptr<Menu_Commands>> commandMap;
};






/***
void GamePausedState::draw() {
	// Draw the game world in a "paused" state
	drawGameWorld();

	// Draw the pause menu
	ImGui::Begin("Paused");

	if (ImGui::Button("Resume")) {
		// Switch to the GameRunningState
	}

	if (ImGui::Button("Display photo")) {
		// Display the photo
	}

	// ...

	ImGui::End();
}*/