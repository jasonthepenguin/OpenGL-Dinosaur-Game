#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "LabEngine.h"



class ModelController
{
	public:
		enum class Direction
		{
			FORWARD,
			BACK,
			LEFT,
			RIGHT
		};
	
	ModelController();
	~ModelController();


	glm::vec3 getCurrentLocation();
	float getTravelDistance();
	float getNPCSpeed();

	
	void setCurrentLocation(glm::vec3 tempLocation);
	void setTravelDistance(float tempDistance);
	void setNPCSpeed(float tempSpeed);
	

	void moveModel(Direction m_TravelDirection, float deltaT);


		/***********************************************************************************************************************************************************************
		 * @brief playNextAnimation()
		 * @brief this function is used to play the MD2 models next animation
		 ***********************************************************************************************************************************************************************/

	void playNextAnimation();



private:

	float m_NPCSpeed;
	float m_TravelDistance;
	glm::vec3 m_CurrentLocation;
	Direction m_TravelDirection;
	std::vector<MD2_TEST*> MD2models;
};

