#pragma once

#include <map>
#include <memory>
#include <unordered_map>


#include "Window.h"
#include "EngGUI.h"

#include "GameState.h"
#include "Save_Command.h"
#include "Mouse_Input.h"
#include "QuitCommand.h"
#include "Keyboard_Input.h"
#include "Resume_Command.h"
#include "PauseMenu_Commands.h"
#include "CustomerSupportCommand.h"

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

class PausedGameState : public GameState
{
    public:
        PausedGameState(std::shared_ptr<Window> window, std::shared_ptr<Keyboard_Input> keyboardInput, std::shared_ptr<Mouse_Input> mouseInput, std::shared_ptr<EngGUI> gui);
        ~PausedGameState();

        void handlePlayerInput() override;
        void update() override;
        void generate() override;

    private:



        
        std::shared_ptr<Window>         m_window;
        std::shared_ptr<Mouse_Input>    m_mouseInput;
        
        std::shared_ptr<Keyboard_Input> m_keyboardInput;
        std::shared_ptr<EngGUI>         m_DisplayOptions;
        std::map<std::string, std::shared_ptr<PauseMenu_Commands>> commandMap;

};
