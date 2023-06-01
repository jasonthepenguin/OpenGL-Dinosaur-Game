#pragma once

#include "GameObject.h"

#include <iostream>

#include "Model.h"
#include <string>


#include "md2_test.h"
#include <memory>


#include "LabEngine.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp> 

#include <cstdlib>
#include <cmath>


// physics/collision detection
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;


// FSM
#include "State.h"
#include "StateMachine.h"

// TESTING



enum MessageType {

};


/*******************************************************************************
 * @class   : NPC
 * @brief   : Updates, Renders, and initializes an npc
 * 
 * @author  : William Halling 32233703
 * @version : 1.0
 * @date    : April 2023 
 *******************************************************************************/

class NPC : public GameObject
{
public:


	std::string filepath = "null";
	Model* ourModel = nullptr;
	std::vector<std::unique_ptr<MD2_TEST>> MD2models;

	StateMachine<NPC>* npcFSM;

	bool cooldown = false;
	float cooldownTime = 3.0;
	float lastTime = 0.0f;

	bool getCooldown();

	glm::vec3 spawnPoint;
	glm::vec3 wanderDirection;


	float walkingSpeed = 1.85f;

	//State

	NPC();

		/***********************************************************
		 * @brief : Update
		 * @brief : Updates the NPCS current location
		 * 
		 * @param : deltaTime - float
		 **********************************************************/
	
	void Update(float deltaTime) override;


		/***********************************************************
		 * @brief : Render
		 * @brief : Renders the NPC into the scene
		 * 
		 * @param : shader - Shader object
		 **********************************************************/
	
	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;



		/***********************************************************
		 * @brief : Init
		 * @brief : Intializes the NPC so its ready to be loaded and work in the scene
		 * 
		 * @param :
		 **********************************************************/
	
	void Init() override;


	bool loadMD2Model(std::string filePath, std::string texturePath);


	// Behaviour methods
	void lookAtplayer();
	void playAnimation(std::string animationName);
	void moveToPlayer();
	int distanceToPlayer();
	void chooseRandomDirection();
	void wander();
	void ForwardLook();


	void collisionEvent(GameObject* gameObj) override;


	~NPC();
};