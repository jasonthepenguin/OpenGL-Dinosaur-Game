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

// TEXTURE GENERATION
#include "TextureGenerator.h"

using namespace reactphysics3d;


class Terrain : public GameObject
{
public:
    float* heightData;
    int size;
    float scaleX;
    float scaleY;
    float scaleZ;
    Shader* sharedShader;
    unsigned char* terrainData;
    rp3d::RigidBody* concaveMeshBody;
    std::vector<float> vertices;
    std::vector<float> vert_pos;
    std::vector<unsigned int> indices;

   
    
    void initializeHeightData();
    void allocateHeightData();
    void normalizeHeightField();
    void generateHeightField(int iterations, int minHeight, int maxHeight, float weight);
    void generateNoTextureVertices();
    void generateTexturedVertices();


    void Update(float deltaTime) override;
    void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;
    void Init() override;
    bool loadHeightfield(const char* filename, const int size);
    void setScalingFactor(float xScale, float yScale, float zScale);
    void bruteForceRender();
    void setUpVertexArrayData();
    void setUpNoTextureAttributes();
    void setUpTexturedAttributes();
    void setupNonTexturedVerts();
    void setUpTerrainData(bool hasTexture);
    void generateNonTexturedTerrain();
    void generateTexturedTerrain();
    void generateVertex(int x, int z);
    void generateVertexWithTexture(int x, int z);
    void generateIndices(int x, int z);



    float getHeight(int xpos, int zpos);
    unsigned char getHeightColor(int xpos, int zpos);
    void normaliseTerrain(float* terData);
    void loadTerrainTexture(std::string textureName);
    bool genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random);
    void addFilter(float* terData, float weight);
    void filterPass(float* startP, int increment, float weight);

    glm::vec3 startPos;


    //------------------------------ TESTING OUT PROCEDURAL TEXTURE GENERATION

    bool addProceduralTexture(const char* filename);

    bool createProceduralTexture();

    float getUnscaledHeight(int xpos, int zpos);

    void getTexCoords(int texNum, unsigned int& x, unsigned int& y);




private:
    Shader* ourShader = nullptr;
    unsigned int VBO, VAO, EBO;
    bool hasTexture;
    std::unique_ptr<Texture> terrainTexture;
    textureGenerator tex;
};



