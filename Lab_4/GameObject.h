#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "telegram.h"
#include "AABB.h"

#include <string>

/**
 * @class  GameObject
 * @brief  Contains data relating to a game object such as its size, position, and rotation.
 * @brief  Potentially look at updating this to a Factory Method Pattern design.
 *
 * @author Jason
 * @date   April 2023
 * @version 1.0
 */
class GameObject
{
public:
    glm::vec3 position;
    glm::mat4 rotation; // testing collision rotations with this
    glm::vec3 size;
    Shader* sharedShader; // might use this or just pass in a shader every time we draw
    std::string name;
    LabPhysics::AABB* boundingBox = nullptr;

    /**
     * @brief  Handles collision events with other game objects.
     * @param  gameObj Pointer to the game object involved in the collision.
     */
    virtual void collisionEvent(GameObject* gameObj)
    {
    }

    /**
     * @brief  Returns the AABB (Axis-Aligned Bounding Box) of the game object.
     * @return Pointer to the AABB if it exists, otherwise nullptr.
     */
    LabPhysics::AABB* getAABB()
    {
        if (boundingBox != nullptr)
        {
            return boundingBox;
        }
        else {
            return nullptr;
        }
    }

    /**
     * @brief  Default constructor.
     */
    GameObject() {
        id = getNextID();
        // std::cout << "Current ID : " << id << std::endl;
    }

    /**
     * @brief  Returns the ID of the game object.
     * @return The ID of the game object.
     */
    int getID() const
    {
        return id;
    }

    /**
     * @brief  Handles the received message.
     * @param  msg The telegram containing the message data.
     * @return True if the message was handled, false otherwise.
     */
    virtual bool handleMessage(const telegram& msg)
    {
        return false;
    }

    /**
     * @brief  Updates the game object.
     * @param  deltaTime The time elapsed since the last update.
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief  Renders the game object.
     * @param  shader     The shader used for rendering.
     * @param  view       The view matrix.
     * @param  projection The projection matrix.
     */
    virtual void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) = 0;

    /**
     * @brief  Initializes the game object.
     */
    virtual void Init() = 0;

protected:
    int id; // unique individual ID
    static int nextID;

    /**
     * @brief  Gets the next available ID for a game object.
     * @return The next available ID.
     */
    int getNextID()
    {
        return nextID++;
    }
};

/**
 * @brief  Static member initialization for the nextID variable.
 */
inline int GameObject::nextID = 0;
