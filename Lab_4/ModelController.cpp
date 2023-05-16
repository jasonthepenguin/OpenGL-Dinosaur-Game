#include "ModelController.h"






glm::vec3 ModelController::getCurrentLocation() { return m_CurrentLocation; }
float     ModelController::getTravelDistance()  { return m_TravelDistance;  }
float     ModelController::getNPCSpeed()        { return m_NPCSpeed;        }


void ModelController::setCurrentLocation(glm::vec3 tempLocation) { m_CurrentLocation = tempLocation; }
void ModelController::setTravelDistance(float tempDistance)      { m_TravelDistance  = tempDistance; }
void ModelController::setNPCSpeed(float tempSpeed)               { m_NPCSpeed        = tempSpeed;    }



void ModelController::moveModel(Direction m_TravelDirection, float deltaT)
{
    glm::vec3 m_NPC_Location = getCurrentLocation();

    switch (m_TravelDirection)
    {
        case Direction::FORWARD:
            m_NPC_Location.x += deltaT;
        break;

        case Direction::BACK:
            m_NPC_Location.x -= deltaT;
        break;
    
        case Direction::LEFT:
            m_NPC_Location.z += deltaT;
        break;

        case Direction::RIGHT:
            m_NPC_Location.z -= deltaT;
        break;


        default:
            return;
    }
    // Move the player camera in the determined direction
    //setCurrentLocation(getCurrentLocation() + m_TravelDirection * m_NPCSpeed * deltaT);
}

 

/*
if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_T) == GLFW_PRESS) {
	model->m_position.z -= deltaValue;
}
if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_PRESS) {
	model->m_position.x -= deltaValue;
}
if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_G) == GLFW_PRESS) {
	model->m_position.z += deltaValue;
}
if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_H) == GLFW_PRESS) {
	model->m_position.x += deltaValue;
}





void MovementKeys::movePlayer(Directions direction, float deltaT)
{
    glm::vec3 movementDirection;

    // Determine the movement direction based on the given direction
    switch (direction)
    {
    case Directions::FORWARD:
        movementDirection = m_PlayerCamera->getCameraDirection();
        break;


    case Directions::BACK:
        movementDirection = -m_PlayerCamera->getCameraDirection();
        break;


    case Directions::LEFT:
        movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getVerticalPlane(), m_PlayerCamera->getCameraDirection()));
        break;


    case Directions::RIGHT:
        movementDirection = glm::normalize(glm::cross(m_PlayerCamera->getCameraDirection(), m_PlayerCamera->getVerticalPlane()));
        break;

    default:
        return; // Invalid direction, do nothing
    }

    // Move the player camera in the determined direction
    m_PlayerCamera->setCameraLocation(m_PlayerCamera->getCameraLocation() + movementDirection * m_PlayerSpeed * deltaT);
}




void ModelController::readInput(GLFWwindow * m_PixelsWindow, float deltaT)
{
    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        moveModel(Direction::FORWARD, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        moveModel(Direction::BACK, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        moveModel(Direction::LEFT, deltaT);
    }

    if (glfwGetKey(m_PixelsWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        moveModel(Direction::RIGHT, deltaT);
    }
}
**/