#pragma once

#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class Player : public GameObject
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


	void Update(float deltaTime) override; // update physics etc

	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override; // draw cube to the screen

	void Init() override; // eg init vertex attribs, setup physics

	void collisionEvent(GameObject* gameObj) override;


private:
	float	  m_PlayerSpeed;
	glm::vec3 m_PlayerLocation;
	glm::vec3 m_PlayerDirection;


};