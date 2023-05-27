#include "GameStateManager.h"



GameStateManager& GameStateManager::getInstance()
{
    static GameStateManager gameInstance;

    return gameInstance;
}


//void GameStateManager::setGameState(std::unique_ptr<GameState> newState)
{
    m_CurrentState = std::move(newState);
}



void GameStateManager::handlePlayerInput()
{
    if (m_CurrentState)
    {
        m_CurrentState->handlePlayerInput();
    }
}


void GameStateManager::generate()
{
    if (m_CurrentState)
    {
        m_CurrentState->generate();
    }
}


void GameStateManager::draw() 
{
    if (m_CurrentState)
    {
        m_CurrentState->draw();
    }
}