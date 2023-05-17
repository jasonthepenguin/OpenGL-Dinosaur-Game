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
}


#include "LabEngine.h"

void MovementKeys::movePlayer(Directions direction, float deltaT)
{
    glm::vec3 movementDirection(0.0f, 0.0f, 0.0f);
   // glm::vec3 movementDirection;


    float velocity = 2.5f * deltaT;

    // Determine the movement direction based on the given direction
    switch (direction)
    {
        case Directions::FORWARD:

            movementDirection += LabEngine::getInstance().m_camera->getCameraDirection() * velocity;
          //  movementDirection += m_PlayerCamera->getCameraDirection();
           // std::cout << "WE ARE GOING FORWARD!!!" << std::endl;
        break;
       
        
        case Directions::BACK:
           // movementDirection -= m_PlayerCamera->getCameraDirection();
            movementDirection -= LabEngine::getInstance().m_camera->getCameraDirection() * velocity;
        break;
       
        
        case Directions::LEFT:
           // movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), -m_PlayerCamera->getHorizontalPlane()));
            movementDirection = glm::normalize(glm::cross(LabEngine::getInstance().m_camera->getCameraDirection(), -glm::vec3(0.0, 1.0, 0.0))) * velocity;

        break;
        
        
        case Directions::RIGHT:
           // movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), m_PlayerCamera->getHorizontalPlane()));
            movementDirection = glm::normalize(glm::cross(LabEngine::getInstance().m_camera->getCameraDirection(), glm::vec3(0.0, 1.0, 0.0))) * velocity;

        break;
        

        default:
            return; // Invalid direction, do nothing
    }

   // m_PlayerCamera->setCameraLocation(m_PlayerCamera->getCameraLocation() + movementDirection * m_PlayerSpeed * deltaT);

   // LabEngine::getInstance().m_camera->setCameraLocation(LabEngine::getInstance().m_camera->getCameraLocation() + movementDirection * m_PlayerSpeed * deltaT);

    LabEngine::getInstance().m_camera->setCameraLocation(LabEngine::getInstance().m_camera->getCameraLocation() + movementDirection);


  //  std::cout << "pos is now : " << LabEngine::getInstance().m_camera->getCameraLocation().x << " , " << LabEngine::getInstance().m_camera->getCameraLocation().y
   //     << " , " << LabEngine::getInstance().m_camera->getCameraLocation().z << std::endl;
}
