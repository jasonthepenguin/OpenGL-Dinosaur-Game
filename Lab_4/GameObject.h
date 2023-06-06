#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "AABB.h"

#include <string>

	/***********************************************************************************************
	 * @class  : GameObject
	 * @brief  : Contains data relating to a game object such as its size, positon, and its rotation.
	 * @brief  : Potentially look at updating this to a Factory Method Pattern design
	 * 
	 * @author  : Jason
	 * @date    : April 2023
	 * @version : 1.0
	 ***********************************************************************************************/

class GameObject
{

	public:

		glm::vec3 position;
		glm::mat4 rotation; // testing collision rotations with this
		glm::vec3 size;


		Shader* sharedShader; // might use this or just pass in a shader everytime we draw

		std::string name;

		LabPhysics::AABB* boundingBox = nullptr;
		virtual void collisionEvent(GameObject* gameObj)
		{

		}

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

		GameObject() {
			id = getNextID();
			//std::cout << "Current ID : " << id << std::endl;
		}


		    /********************************************************************************************************
             * @brief : Update
             * @brief : Virtual void as it will be overriden by a child class and updated for each object
             ********************************************************************************************************/

		virtual void Update(float deltaTime) = 0;


		    /********************************************************************************************************
             * @brief : Render
             * @brief : Virtual void as it will be overriden by a child class as each child object will be rendered
             ********************************************************************************************************/

		virtual void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) = 0;


		    /********************************************************************************************************
             * @brief : Init
             * @brief : Virtual void as it will be overriden by a child class as each child object will be Initialized
             ********************************************************************************************************/

		virtual void Init() = 0;

protected:

	int id; // unique individual ID

	static int nextID;



	int getNextID()
	{
		return nextID++;

	}

};

inline int GameObject::nextID = 0;