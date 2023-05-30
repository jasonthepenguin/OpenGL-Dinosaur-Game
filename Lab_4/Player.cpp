#include "Player.h"


Player::Player(const std::string tempPlayerName, const glm::vec3& tempPlayerLocaiton, float& tempPlayerSpeed, int tempPlayerScore, const Camera& tempPlayerCamera) :
	m_PlayerName(tempPlayerName),
	m_PlayerLocation(tempPlayerLocaiton),
	m_PlayerSpeed(tempPlayerSpeed),
	m_PlayerScore(tempPlayerScore),
	m_PlayerCamera(tempPlayerCamera) 

{}


Player::~Player()
{

}



std::string		 Player::getPlayerName()     const { return m_PlayerName;					    }
const glm::vec3& Player::getPlayerLocation() const { return m_PlayerCamera.getCameraLocation(); }
float			 Player::getPlayerSpeed()	 const { return m_PlayerSpeed;						}				
int              Player::getPlayerScore()    const { return m_PlayerScore;						}
const Camera&	 Player::getPlayerCamera()   const { return m_PlayerCamera;						}



void Player::setPlayerName(std::string tempPlayerName)			    { m_PlayerName     = tempPlayerName;	 }
void Player::setPlayerLocation(const glm::vec3& tempPlayerLocation) { m_PlayerLocation = tempPlayerLocation; }
void Player::setPlayerSpeed(const float& tempPlayerSpeed)			{ m_PlayerSpeed    = tempPlayerSpeed;    }
void Player::setPlayerScore(int tempPlayerScore)					{ m_PlayerScore    = tempPlayerScore;    }
void Player::setPlayerCamera(const Camera& tempPlayerCamera)        { m_PlayerCamera   = tempPlayerCamera;   }

