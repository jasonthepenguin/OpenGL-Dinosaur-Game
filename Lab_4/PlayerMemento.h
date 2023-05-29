#pragma once
#include "Player.h"


/// <summary>
/// stores and restores the state of the player



class PlayerMemento
{
public:
	PlayerMemento(Player& player);
	void restore();


private:

	float	  m_PlayerSpeed;
	glm::vec3 m_PlayerLocation;
	glm::vec3 m_PlayerDirection;

	Player* m_Player; // Reference to the original player
};

