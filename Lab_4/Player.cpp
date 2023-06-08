#include "Player.h"


Player::Player()
{
    // TODO: Implement default constructor
   // playerCamera = LabEngine::getInstance().m_camera;

}

Player::Player(const glm::vec3& spawnLocation, const glm::vec3& currentDirection, const float& playerSpeed)
{
    // TODO: Implement parameterized constructor
}

float Player::getPlayerSpeed()
{
    // TODO: Implement getPlayerSpeed
    return 0.0f;
}

glm::vec3 Player::getPlayerLocation()
{
    // TODO: Implement getPlayerLocation
    return glm::vec3(0.0f);
}

glm::vec3 Player::getPlayerDirection()
{
    // TODO: Implement getPlayerDirection
    return glm::vec3(0.0f);
}

void Player::setPlayerSpeed(const float& speed)
{
    // TODO: Implement setPlayerSpeed
}

void Player::setPlayerLocation(const glm::vec3& location)
{
    // TODO: Implement setPlayerLocation
}

void Player::setPlayerDirection(const glm::vec3& direction)
{
    // TODO: Implement setPlayerDirection
}


void Player::Update(float deltaTime)
{
    // Update physics and other game-related logic here
    m_PlayerLocation = LabEngine::getInstance().m_camera->getCameraLocation();
   // oldPosition = m_PlayerLocation; ( we already got this due to our poorly design choices in movementkeys.cpp )


    boundingBox->updateAABBPosition(m_PlayerLocation);
}

void Player::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
    // Draw cube to the screen
}

void Player::Init()
{

    boundingBox = new LabPhysics::AABB(glm::vec3(1, 3, 1));
}

void Player::collisionEvent(GameObject* gameObj)
{
    // Handle collision event with another player here
    LabEngine::getInstance().m_camera->setCameraLocation(oldPosition);

    boundingBox->updateAABBPosition(oldPosition);
    //std::cout << "Player collided with something!" << std::endl;

    Prop* prop = dynamic_cast<Prop*>(gameObj);
    if (prop != nullptr)
    {

    }

    
}