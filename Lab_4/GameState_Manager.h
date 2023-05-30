#pragma once
#include <memory>
#include "GameState.h"

/***************************************************************************************************************
 * @brief : GameStateManager
 * @brief :
 *
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class GameState_Manager
{
    public:

        static GameState_Manager& getInstance()
        {
            static GameState_Manager instance;

            return instance;
        }


        void setGameState(std::unique_ptr<GameState> newState);
        void handlePlayerInput();
        void generate();


private:
    GameState_Manager() = default;

    GameState_Manager(const GameState_Manager&) = delete;
    GameState_Manager& operator=(const GameState_Manager&) = delete;
    GameState_Manager(GameState_Manager&&) = delete;
    GameState_Manager& operator=(GameState_Manager&&) = delete;

	std::unique_ptr<GameState> m_CurrentState;
};
