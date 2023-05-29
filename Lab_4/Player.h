#pragma once


class Player
{
public:
	Player();
	Player(const glm::vec3& spawnLocation, const glm::vec3& currentDirection, const float& playerSpeed);


	float	  getPlayerSpeed();
	glm::vec3 getPlayerLocation();
	glm::vec3 getPlayerDirection();


	void setPlayerSpeed(const float& speed);
	void setPlayerLocation(const glm::vec3& location);
	void setPlayerDirection(const glm::vec3& direction);


private:
	float	  m_PlayerSpeed;
	glm::vec3 m_PlayerLocation;
	glm::vec3 m_PlayerDirection;
};