#pragma once

#include <map>
#include <memory>

class Window {};
class Menu_Commands {};

class Mouse_Input {};
class Keyboard_Input {};
class EngGUI {};
class ResumeCommand : public Menu_Commands {};
class SaveCommand : public Menu_Commands {};
class UI_Manager {};


/***************************************************************************************************************
 * @brief : IGameState
 * @brief :
 *
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class GameState 
{
    public:
        virtual ~GameState() = default;
        virtual void handlePlayerInput() = 0;
        virtual void Enter()    = 0;
        virtual void generate() = 0;
        virtual void update()   = 0;
        virtual void Exit()     = 0;
};