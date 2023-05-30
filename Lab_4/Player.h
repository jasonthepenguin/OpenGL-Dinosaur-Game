#pragma once


#include "Camera.h"

#include <string.h>
#include <iostream>
#include <glm/glm.hpp>



class Player
{
	public:
		Player();
		Player(const std::string tempPlayerName, const glm::vec3& tempPlayerLocaiton, float& tempPlayerSpeed, int tempPlayerScore, const Camera& tempPlayerCamera);
		~Player();

	
		std::string getPlayerName() const;
		
		const glm::vec3& getPlayerLocation() const;
		float getPlayerSpeed() const;
		int   getPlayerScore() const;
		const Camera& getPlayerCamera() const;



		void setPlayerName(std::string tempPlayerName);
		void setPlayerLocation(const glm::vec3& tempPlayerLocaiton);
		void setPlayerSpeed(const float& tempPlayerSpeed);
		void setPlayerScore(int tempPlayerScore);
		void setPlayerCamera(const Camera& tempPlayerCamera);


	private:

		std::string m_PlayerName;
		float	    m_PlayerSpeed;
		int			m_PlayerScore;
		Camera	    m_PlayerCamera;
		glm::vec3   m_PlayerLocation;
		glm::vec3   m_PlayerDirection;
};


