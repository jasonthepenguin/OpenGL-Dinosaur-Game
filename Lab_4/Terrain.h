#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include <memory>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include <reactphysics3d/reactphysics3d.h>
#include "TextureGenerator.h"

using namespace reactphysics3d;

/**
 * @class Terrain
 * @brief Terrain class inherited from GameObject. Represents the terrain of the game.
 */
class Terrain : public GameObject
{
public:
    float* heightData; ///< Pointer to the height data array.
    int size; ///< Size of the terrain.
    float scaleX; ///< Scale in the x dimension.
    float scaleY; ///< Scale in the y dimension.
    float scaleZ; ///< Scale in the z dimension.
    Shader* sharedShader; ///< Shared shader used for rendering.
    unsigned char* terrainData; ///< Pointer to the terrain data array.
    rp3d::RigidBody* concaveMeshBody; ///< Concave mesh body for the terrain physics.
    std::vector<float> vertices; ///< Vector storing all vertices data.
    std::vector<float> vert_pos; ///< Vector storing position of vertices.
    std::vector<unsigned int> indices; ///< Vector storing indices for the vertices.

    /**
     * @brief Initialize height data.
     */
    void initializeHeightData();

    /**
     * @brief Allocate space for height data.
     */
    void allocateHeightData();

    /**
     * @brief Normalize the height field data.
     */
    void normalizeHeightField();

    /**
     * @brief Generate the height field.
     */
    void generateHeightField(int iterations, int minHeight, int maxHeight, float weight);

    /**
     * @brief Generate vertices without texture.
     */
    void generateNoTextureVertices();

    /**
     * @brief Generate textured vertices.
     */
    void generateTexturedVertices();

    /**
     * @brief Update the terrain.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Render the terrain.
     */
    void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;

    /**
     * @brief Initialize the terrain.
     */
    void Init() override;

    /**
     * @brief Load heightfield from a file.
     */
    bool loadHeightfield(const char* filename, const int size);

    /**
     * @brief Set the scaling factors for the terrain.
     */
    void setScalingFactor(float xScale, float yScale, float zScale);

    /**
     * @brief Render the terrain using brute force.
     */
    void bruteForceRender();

    /**
     * @brief Set up the vertex array data.
     */
    void setUpVertexArrayData();

    /**
     * @brief Set up the non-texture attributes.
     */
    void setUpNoTextureAttributes();

    /**
     * @brief Set up the textured attributes.
     */
    void setUpTexturedAttributes();

    /**
     * @brief Set up the non-textured vertices.
     */
    void setupNonTexturedVerts();

    /**
     * @brief Set up the terrain data.
     */
    void setUpTerrainData(bool hasTexture);

    /**
     * @brief Generate non-textured terrain.
     */
    void generateNonTexturedTerrain();

    /**
     * @brief Generate textured terrain.
     */
    void generateTexturedTerrain();

    /**
     * @brief Generate vertex at a specific location.
     */
    void generateVertex(int x, int z);

    /**
     * @brief Generate textured vertex at a specific location.
     */
    void generateVertexWithTexture(int x, int z);

    /**
     * @brief Generate indices at a specific location.
     */
    void generateIndices(int x, int z);

    /**
     * @brief Get height at a specific location.
     */
    float getHeight(int xpos, int zpos);

    /**
     * @brief Get height color at a specific location.
     */
    unsigned char getHeightColor(int xpos, int zpos);

    /**
     * @brief Normalize terrain data.
     */
    void normaliseTerrain(float* terData);

    /**
     * @brief Load terrain texture.
     */
    void loadTerrainTexture(std::string textureName);

    /**
     * @brief Generate fault formation.
     */
    bool genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random);

    /**
     * @brief Add filter to the terrain data.
     */
    void addFilter(float* terData, float weight);

    /**
     * @brief Execute a filter pass.
     */
    void filterPass(float* startP, int increment, float weight);

    glm::vec3 startPos; ///< Starting position of the terrain.

    /**
     * @brief Add procedural texture to the terrain.
     */
    bool addProceduralTexture(const char* filename);

    /**
     * @brief Create procedural texture for the terrain.
     */
    bool createProceduralTexture();

    /**
     * @brief Get the unscaled height at a specific location.
     */
    float getUnscaledHeight(int xpos, int zpos);

    /**
     * @brief Get texture coordinates.
     */
    void getTexCoords(int texNum, unsigned int& x, unsigned int& y);

private:
    Shader* ourShader; ///< Private shader for the terrain.
    unsigned int VBO, VAO, EBO; ///< Buffers for storing vertices data.
    bool hasTexture; ///< Flag for texture presence.
    std::unique_ptr<Texture> terrainTexture; ///< Unique pointer to the texture.
    textureGenerator tex; ///< Texture generator object.
};
