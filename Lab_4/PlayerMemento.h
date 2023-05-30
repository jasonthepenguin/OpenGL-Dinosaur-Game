#pragma once
#include "Player.h"


class PlayerMemento
{
public:
	PlayerMemento(Player& player);
	void restore();


private:

	Player&   m_Player;
	float     m_PlayerSpeed;
	glm::vec3 m_PlayerLocation;
	glm::vec3 m_PlayerDirection;
};

