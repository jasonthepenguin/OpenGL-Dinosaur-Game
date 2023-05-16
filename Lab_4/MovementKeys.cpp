#include "MovementKeys.h"

MovementKeys::MovementKeys()
{

}


MovementKeys::~MovementKeys() {}


MovementKeys::Directions MovementKeys::getDirections() const { return m_CurrentDirection; }
float MovementKeys::getPlayerSpeed()                   const { return m_PlayerSpeed;      }
void MovementKeys::setPlayerSpeed(float tempSpeed)           { m_PlayerSpeed = tempSpeed; }



void MovementKeys::readInput(GLFWwindow* m_PixelsWindow, float deltaT)
{
    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        movePlayer(Directions::FORWARD, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        movePlayer(Directions::BACK, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        movePlayer(Directions::LEFT, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        movePlayer(Directions::RIGHT, deltaT);
    }
}



void MovementKeys::movePlayer(Directions direction, float deltaT)
{
    glm::vec3 movementDirection;

    // Determine the movement direction based on the given direction
    switch (direction)
    {
        case Directions::FORWARD:
            movementDirection += m_PlayerCamera->getCameraDirection();
        break;
       
        
        case Directions::BACK:
            movementDirection -= m_PlayerCamera->getCameraDirection();
        break;
       
        
        case Directions::LEFT:
            movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), -m_PlayerCamera->getHorizontalPlane()));
        break;
        
        
        case Directions::RIGHT:
            movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), m_PlayerCamera->getHorizontalPlane()));
        break;
        

        default:
            return; // Invalid direction, do nothing
    }

    m_PlayerCamera->setCameraLocation(m_PlayerCamera->getCameraLocation() + movementDirection * m_PlayerSpeed * deltaT);
}
