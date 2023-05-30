#include "GameRunning_State.h"

GameRunning_State::GameRunning_State(std::shared_ptr<UI_Manager> uiManager) : m_UIManager(std::move(uiManager))
{

}


void GameRunning_State::handlePlayerInput()
{
	//m_UIManager->readUserInput(window, deltaT);
}


void GameRunning_State::update()
{

}


void GameRunning_State::generate()
{

}