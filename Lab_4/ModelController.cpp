#include "ModelController.h"

ModelController::ModelController()
{

}

ModelController::~ModelController()
{

}

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
    setCurrentLocation(m_NPC_Location);
}

 


void ModelController::playNextAnimation()
{
    auto& engRef = LabEngine::getInstance();

    for (auto model : engRef.MD2models)
    {
        model->playNextAnimation();
    }
}
