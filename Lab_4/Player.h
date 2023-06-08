#pragma once

#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include "LabEngine.h"

#include "PhysicsController.h"
#include "Prop.h"

#include <memory>

/**
 * @brief The Player class represents a player object in the game.
 */
class Player : public GameObject
{
public:
    /**
     * @brief Default constructor for the Player class.
     */
    Player();

    /**
     * @brief Constructs a Player object with the specified spawn location, current direction, and player speed.
     * @param spawnLocation The initial location of the player.
     * @param currentDirection The initial direction of the player.
     * @param playerSpeed The speed of the player.
     */
    Player(const glm::vec3& spawnLocation, const glm::vec3& currentDirection, const float& playerSpeed);

    /**
     * @brief Retrieves the speed of the player.
     * @return The speed of the player.
     */
    float getPlayerSpeed();

    /**
     * @brief Retrieves the location of the player.
     * @return The location of the player.
     */
    glm::vec3 getPlayerLocation();

    /**
     * @brief Retrieves the direction of the player.
     * @return The direction of the player.
     */
    glm::vec3 getPlayerDirection();

    /**
     * @brief Sets the speed of the player.
     * @param speed The new speed of the player.
     */
    void setPlayerSpeed(const float& speed);

    /**
     * @brief Sets the location of the player.
     * @param location The new location of the player.
     */
    void setPlayerLocation(const glm::vec3& location);

    /**
     * @brief Sets the direction of the player.
     * @param direction The new direction of the player.
     */
    void setPlayerDirection(const glm::vec3& direction);

    /**
     * @brief Updates the player's state.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Renders the player object.
     * @param shader The shader used for rendering.
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;

    /**
     * @brief Initializes the player object.
     */
    void Init() override;

    /**
     * @brief Handles collision events with other game objects.
     * @param gameObj The game object involved in the collision.
     */
    void collisionEvent(GameObject* gameObj) override;

    glm::vec3 oldPosition; /**< The previous position of the player. */

private:
    float m_PlayerSpeed; /**< The speed of the player. */
    glm::vec3 m_PlayerLocation; /**< The location of the player. */
    glm::vec3 m_PlayerDirection; /**< The direction of the player. */

    // std::shared_ptr<Camera> playerCamera;
};
