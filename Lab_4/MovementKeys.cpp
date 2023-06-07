#include "MovementKeys.h"


#include <iostream>

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


    auto MD2models = LabEngine::getInstance().MD2models;
    // test to move the MD2 model

}



void MovementKeys::movePlayer(Directions direction, float deltaT)
{
    glm::vec3 movementDirection(0.0f, 0.0f, 0.0f);

    float velocity = 5.0f * deltaT;

    // Determine the movement direction based on the given direction
    switch (direction)
    {
        case Directions::FORWARD:

            movementDirection += LabEngine::getInstance().m_camera->getCameraDirection() * velocity;

        break;
       
        
        case Directions::BACK:
          
            movementDirection -= LabEngine::getInstance().m_camera->getCameraDirection() * velocity;
        
       break;
       
        
        case Directions::LEFT:
            movementDirection = glm::normalize(glm::cross(LabEngine::getInstance().m_camera->getCameraDirection(), -glm::vec3(0.0, 1.0, 0.0))) * velocity;

        break;
        
        
        case Directions::RIGHT:
            movementDirection = glm::normalize(glm::cross(LabEngine::getInstance().m_camera->getCameraDirection(), glm::vec3(0.0, 1.0, 0.0))) * velocity;

        break;
        

        default:
            return; // Invalid direction, do nothing
    }

    LabEngine::getInstance().m_camera->setCameraLocation(LabEngine::getInstance().m_camera->getCameraLocation() + movementDirection);
}
