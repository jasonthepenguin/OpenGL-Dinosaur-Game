#pragma once

#include "GameObject.h"

#include "Model.h"
#include <string>


// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>



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
	
	void Render(Shader& shader) override;



		/***********************************************************
		 * @brief : Init
		 * @brief : Intializes the NPC so its ready to be loaded and work in the scene
		 * 
		 * @param :
		 **********************************************************/
	
	void Init() override;

};