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

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "GameObject.h"

//#include "LabEngine.h"


#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;


/**********************


 **********************/
class Terrain : public GameObject 
{
	public:



		int size; // the size of the hightfield along x and z - power of 2 ( for bruteforce )


		float scaleX;
		float scaleY;
		float scaleZ;


		Shader* sharedShader;

		unsigned char* terrainData;
		rp3d::RigidBody* concaveMeshBody;


		std::vector<float> vertices;

		std::vector<float> vert_pos; // JUST TEMPORARILY TEST COLLISIONS

		std::vector<unsigned int> indices; // trying to make the terrain render propely ( not look layered )


		// step 2 
		bool loadHeightfield(const char* fileName, const int size);
		// step 3 
		void setScalingFactor(float xScale, float yScale, float zScale);
		// step 4 (render heightfield)
		//void bruteForceRender(glm::mat4 projection, glm::mat4 view);
		void bruteForceRender();

		float getHeight(int xpos, int zpos);
		unsigned char getHeightColor(int xpos, int zpos);

		void normaliseTerrain(float* terData);

		void loadTerrainTexture(std::string textureName);


		//----------------------- FAULT FORMATION SECTION
		bool genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random);
		void addFilter(float* terData, float weight);
		void filterPass(float* startP, int increment, float weight);

		//---------------------

		glm::vec3 startPos;
		bool setUpTerrainData(bool hasTexture);
		void Update(float deltaTime) override; // 

		void Render(Shader& shader) override; // 
		void Init() override; 


	private:
		
		Shader* ourShader = nullptr;
		unsigned int VBO, VAO, EBO;
		bool hasTexture;
		std::unique_ptr<Texture> terrainTexture;

};



