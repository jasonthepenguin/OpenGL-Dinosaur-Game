#pragma once
#include <memory>
#include "IGameState.h"


class GameStateManager
{
    public:

        static GameStateManager& getInstance() 
        {
            static GameStateManager instance;

            return instance;
        }


        void setGameState(std::unique_ptr<IGameState> newState);
        void handlePlayerInput();
        void generate();
        void draw();


    private:

        GameStateManager() = default;
        static GameStateManager& getInstance();
        std::unique_ptr<IGameState> m_CurrentState;


        GameStateManager(const GameStateManager&)            = delete;
        GameStateManager& operator=(const GameStateManager&) = delete;
        GameStateManager(GameStateManager&&)                 = delete;
        GameStateManager& operator=(GameStateManager&&)      = delete;

        std::unique_ptr<IGameState> m_CurrentState;
};
