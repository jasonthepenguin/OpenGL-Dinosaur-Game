#include "Player.h"

#include "Player.h"

Player::Player()
{
    // TODO: Implement default constructor
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
}

void Player::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
    // Draw cube to the screen
}

void Player::Init()
{
    // Initialize vertex attributes, setup physics, and other initialization tasks here
}

void Player::collisionEvent(GameObject* gameObj)
{
    // Handle collision event with another player here
}