#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"

/**
 * @brief A class representing a water object.
 */
class Water {
public:
    /**
     * @brief Default constructor for the Water class.
     */
    Water() : _vao(0), _vbo(0), _ebo(0), waterShader(nullptr), size(5.0)
    {
        position.x = 0.0f;
        position.y = 0.0f;
        position.z = 0.0f;
    }

    /**
     * @brief Destructor for the Water class.
     */
    ~Water() {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
    }

    /**
     * @brief Initializes the water object.
     */
    void init() {
        TextureFactory textFact; // temporarily placing this here.
        waterText = textFact.createTexture("textures/water.jpg");
        waterText->load();

        std::vector<GLfloat> vertices = {
            // Position       // Texture Coordinates
            -0.5f, 0.0f, -0.5f,  0.0f, 1.0f,
             0.5f, 0.0f, -0.5f,  1.0f, 1.0f,
             0.5f, 0.0f,  0.5f,  1.0f, 0.0f,
            -0.5f, 0.0f,  0.5f,  0.0f, 0.0f
        };

        // Create water plane index data
        std::vector<GLuint> indices = {
            0, 1, 2,
            2, 3, 0
        };

        // Generate VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        // Generate VBO
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        // Generate EBO
        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture coordinates attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // Unbind VAO
        glBindVertexArray(0);

        waterShader = new Shader("shaders/water/water_vs.shader", "shaders/water/water_fs.shader");

        waterShader->setInt("waterTexture", 0);
    }

    /**
     * @brief Updates the water object.
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime) {
        // Update water state if needed
    }

    /**
     * @brief Renders the water object.
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    void render(const glm::mat4& view, const glm::mat4& projection) {
        waterShader->use();
        waterShader->setMat4("view", view);
        waterShader->setMat4("projection", projection);

        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f, size));
        model = glm::translate(model, position);

        waterShader->setMat4("model", model);

        glBindVertexArray(_vao);

        waterText->bindTexture(0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    /**
     * @brief Sets the size of the water object.
     * @param newSize The new size of the water object.
     */
    void setSize(float newSize) {
        size = newSize;
    }

    glm::vec3 position; /**< The position of the water object. */
    std::unique_ptr<Texture> waterText; /**< The water texture. */

private:
    GLuint _vao, _vbo, _ebo; /**< Vertex array object (VAO), vertex buffer object (VBO), element buffer object (EBO). */
    Shader* waterShader; /**< The shader used for rendering the water object. */
    float size; /**< The size of the water object. */
};
