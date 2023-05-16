#pragma once

#include <glm/glm.hpp>


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
	
	void controlModel();
	void moveModel(Direction m_TravelDirection, float deltaT);


private:
	float m_NPCSpeed;
	float m_TravelDistance;
	glm::vec3 m_CurrentLocation;
	Direction m_TravelDirection;
};

