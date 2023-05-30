#include "PlayerMemento.h"

PlayerMemento::PlayerMemento(Player& player) : m_Player(player)
{
	m_PlayerSpeed = m_Player.getPlayerSpeed();
	m_PlayerLocation = m_Player.getPlayerLocation();
	m_PlayerDirection = m_Player.getPlayerCamera().getCameraDirection();
}



void PlayerMemento::restore()
{
	// Restore the player's state
	m_Player.setPlayerSpeed(m_PlayerSpeed);
	m_Player.setPlayerLocation(m_PlayerLocation);
	m_Player.getPlayerCamera().setCameraDirection(m_PlayerDirection);
}