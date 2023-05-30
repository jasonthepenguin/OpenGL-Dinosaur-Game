#include "MovementKeys.h"


MovementKeys::MovementKeys() {}

MovementKeys::~MovementKeys() {}

MovementKeys::Directions MovementKeys::getDirections() const { return m_CurrentDirection; }
float					 MovementKeys::getPlayerSpeed() const { return m_PlayerSpeed; }



void MovementKeys::setPlayerSpeed(float tempSpeed) { m_PlayerSpeed = tempSpeed; }


void MovementKeys::onKeyInput(GLFWwindow* window, int key, int action, int mods, float deltaT)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			movePlayer(Directions::FORWARD, deltaT);
			break;

		case GLFW_KEY_S:
			movePlayer(Directions::BACK, deltaT);
			break;

		case GLFW_KEY_A:
			movePlayer(Directions::LEFT, deltaT);
			break;

		case GLFW_KEY_D:
			movePlayer(Directions::RIGHT, deltaT);
			break;

		default:
			break;
		}
	}
}



void MovementKeys::movePlayer(Directions direction, float deltaT)
{
	glm::vec3 movementDirection(0.0f, 0.0f, 0.0f);
	float velocity = m_PlayerSpeed * deltaT;

	// Determine the movement direction based on the given direction
	switch (direction)
	{
	case Directions::FORWARD:
		movementDirection += m_PlayerCamera->getCameraDirection() * velocity;
		break;

	case Directions::BACK:
		movementDirection -= m_PlayerCamera->getCameraDirection() * velocity;
		break;

	case Directions::LEFT:
		movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), -glm::vec3(0.0, 1.0, 0.0))) * velocity;
		break;

	case Directions::RIGHT:
		movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), glm::vec3(0.0, 1.0, 0.0))) * velocity;
		break;

	default:
		return;
	}

	m_PlayerCamera->setCameraLocation(m_PlayerCamera->getCameraLocation() + movementDirection);
}