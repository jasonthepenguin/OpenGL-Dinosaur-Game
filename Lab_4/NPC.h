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

#include "test_cube.h"

// physics/collision detection
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

// FSM
//#include "State.h"
#include "StateMachine.h"

#include <sol/sol.hpp>

// TESTING

enum MessageType {

};

/*******************************************************************************
 * @class   : NPC
 * @brief   : Updates, Renders, and initializes an npc
 *
 * This class represents an NPC (Non-Player Character) in the game. It provides
 * functionality to update its position, render it in the scene, and initialize
 * its resources. It also includes behavior methods for interacting with other
 * game objects and handling messages.
 *
 * Author  : William Halling 32233703
 * Version : 1.0
 * Date    : April 2023
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

	/**
	 * @brief   Check if the NPC is on cooldown.
	 *
	 * @return  true if the NPC is on cooldown, false otherwise.
	 */
	bool getCooldown();

	glm::vec3 spawnPoint;
	glm::vec3 wanderDirection;
	glm::vec3 waypoint;

	glm::vec3 oldPosition;

	float walkingSpeed = 1.85f;

	NPC();

	/***********************************************************
	 * @brief   Update
	 * @brief   Updates the NPC's current location
	 *
	 * This method is called to update the NPC's position in the
	 * game world. It takes the deltaTime as a parameter to
	 * calculate the movement based on time.
	 *
	 * @param   deltaTime - Time elapsed since the last update
	 **********************************************************/
	void Update(float deltaTime) override;

	/***********************************************************
	 * @brief   Render
	 * @brief   Renders the NPC into the scene
	 *
	 * This method is called to render the NPC in the game scene.
	 * It takes a shader, view matrix, and projection matrix as
	 * parameters for rendering the model.
	 *
	 * @param   shader     - Shader object used for rendering
	 * @param   view       - View matrix for the scene
	 * @param   projection - Projection matrix for the scene
	 **********************************************************/
	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override;

	/***********************************************************
	 * @brief   Init
	 * @brief   Initializes the NPC
	 *
	 * This method initializes the NPC by loading its resources
	 * and setting up initial values.
	 **********************************************************/
	void Init() override;

	/***********************************************************
	 * @brief   Load an MD2 model for the NPC
	 *
	 * This method loads an MD2 model for the NPC using the
	 * specified file path and texture path.
	 *
	 * @param   filePath     - File path of the MD2 model
	 * @param   texturePath  - Texture path for the model
	 * @return  true if the model was loaded successfully, false otherwise
	 */
	bool loadMD2Model(std::string filePath, std::string texturePath);

	// Behavior methods

	/***********************************************************
	 * @brief   Make the NPC look at the player
	 *
	 * This method makes the NPC look at the player's position
	 * in the game world.
	 */
	void lookAtplayer();

	/***********************************************************
	 * @brief   Play an animation for the NPC
	 *
	 * This method plays the specified animation for the NPC.
	 *
	 * @param   animationName - Name of the animation to play
	 */
	void playAnimation(std::string animationName);

	/***********************************************************
	 * @brief   Move the NPC towards the player
	 *
	 * This method moves the NPC towards the player's position
	 * in the game world.
	 */
	void moveToPlayer();

	/***********************************************************
	 * @brief   Calculate the distance to the player
	 *
	 * This method calculates the distance between the NPC and
	 * the player in the game world.
	 *
	 * @return  The distance to the player
	 */
	int distanceToPlayer();

	/***********************************************************
	 * @brief   Choose a random direction for the NPC to wander
	 *
	 * This method chooses a random direction for the NPC to
	 * wander in the game world.
	 */
	void chooseRandomDirection();

	/***********************************************************
	 * @brief   Make the NPC wander in the game world
	 *
	 * This method makes the NPC wander in the game world by
	 * moving in the chosen wander direction.
	 */
	void wander();

	/***********************************************************
	 * @brief   Make the NPC look forward in the game world
	 *
	 * This method makes the NPC look forward in the game world
	 * based on its current movement direction.
	 */
	void ForwardLook();

	/***********************************************************
	 * @brief   Handle a collision event with a game object
	 *
	 * This method is called when the NPC collides with a
	 * game object. It takes the collided game object as a
	 * parameter.
	 *
	 * @param   gameObj - Collided game object
	 */
	void collisionEvent(GameObject* gameObj) override;

	/***********************************************************
	 * @brief   Handle a message received by the NPC
	 *
	 * This method is called to handle a message received by
	 * the NPC. It takes the message as a parameter and returns
	 * true if the message was handled successfully, false otherwise.
	 *
	 * @param   msg - The received message
	 * @return  true if the message was handled successfully, false otherwise
	 */
	bool handleMessage(const telegram& msg) override;

	/***********************************************************
	 * @brief   Send a message to another NPC
	 *
	 * This method is used to send a message from the NPC to
	 * another NPC. It takes the delay, sender, receiver, message,
	 * and additional information as parameters.
	 *
	 * @param   delay           - Delay before the message is sent
	 * @param   sender          - ID of the sending NPC
	 * @param   receiver        - ID of the receiving NPC
	 * @param   msg             - Message type
	 * @param   additionalInfo  - Additional information (optional)
	 */
	void sendMessage(double delay, int sender, int receiver, int msg, sol::object additionalInfo);

	/***********************************************************
	 * @brief   Find the closest NPC in the game world
	 *
	 * This method finds the closest NPC to the current NPC in
	 * the game world.
	 *
	 * @return  The ID of the closest NPC
	 */
	int findClosestNPC();

	/***********************************************************
	 * @brief   Set the waypoint for the NPC
	 *
	 * This method sets the waypoint for the NPC to the specified
	 * position in the game world.
	 *
	 * @param   newWaypoint - New waypoint position
	 */
	void setWaypoint(glm::vec3 newWaypoint);

	/***********************************************************
	 * @brief   Move the NPC towards the waypoint
	 *
	 * This method moves the NPC towards the waypoint in the
	 * game world.
	 */
	void moveToWaypoint();

	/***********************************************************
	 * @brief   Calculate the distance to the waypoint
	 *
	 * This method calculates the distance between the NPC and
	 * the waypoint in the game world.
	 *
	 * @return  The distance to the waypoint
	 */
	int distanceToWaypoint();

	/***********************************************************
	 * @brief   Respawn the NPC
	 *
	 * This method respawns the NPC by resetting its position
	 * and other attributes.
	 */
	void respawn();

	~NPC();
};
