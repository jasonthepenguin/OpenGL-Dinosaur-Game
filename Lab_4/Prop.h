#pragma once

#include "GameObject.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "LabEngine.h"

#include "Model.h"

#include <vector>

/**
 * @brief Class representing a prop in the game world.
 *
 * Prop inherits from the GameObject class and provides functionality for updating physics, rendering the prop, and initializing properties.
 */
class Prop : public GameObject
{
public:
    /**
     * @brief Updates the prop's physics and other properties.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Renders the prop using the provided shader, view matrix, and projection matrix.
     *
     * @param shader The shader used for rendering.
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;

    /**
     * @brief Initializes the prop by setting up vertex attributes and physics.
     */
    void Init() override;

    /**
     * @brief List of positions where this prop can be placed.
     */
    std::vector<glm::vec3> positionList;

    /**
     * @brief File path to the model used for rendering the prop.
     */
    std::string modelFilePath;

    /**
     * @brief Pointer to the prop's model object.
     */
    Model* propModel;
};
