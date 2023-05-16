#pragma once


#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Testing texture class
#include "stb_image.h"
#include "Texture.h"

#include "Window.h"
#include "Shader.h"

#include "Camera.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>


// Test object
#include "test_cube.h"
#include "Model.h"
#include "GameObject.h"
#include "NPC.h"

#include "Terrain.h"

// Graphics
#include "Graphics.h"

// GUI
#include "EngGUI.h"


// LUA
#include <lua.hpp>
#include <sol/sol.hpp>
#include "assert.hpp"

// physics/collision detection
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

#include <vector>



#include "md2_test.h"


		/******************************************************************************************************************************************
		 * @class   : LabEngine() 
		 * @brief   : This is the primary engine used to run the program
		 * 
         * @author  : Jason & William
		 * @date    : April 2023
		 * @version : 1.2 - Added all doccumentation
		 ******************************************************************************************************************************************/

//namespace Lab {

	class LabEngine
	{

		public:
		
				/******************************************************************************************************************************************
				 * @brief  Variables for the class() 
				 ******************************************************************************************************************************************/
				
			Window* m_window;  		  /// Window object ptr used to create a window object
			Camera* m_camera;		  /// Camera object the players ingame camera
			float lastX;			  /// lastX 	 - the previous X position
			float lastY;			  /// lastY 	 - the previous Y position 
			bool firstMouse = true;	  /// firstMouse - checks if mouse interacted with

			// Objects
			Terrain *simpleTerrain;   /// object to the terrain class to create a terrain
			std::vector<GameObject*> gameObjects; /// an std::vector of gameObjects to generate game objects
			std::unique_ptr<Graphics> graphics;	  /// an std::unique_ptr<Graphics> used to create the graphics Factory
			EngGUI* gui;						  /// EngGUI  - graphical user interface object
			PhysicsCommon physicsCommon;	/// Physics - a class which contains commonly known physics
			PhysicsWorld* world;			/// PhysicsWorld - applies physics to the game 
			float deltaTime = 0.0f;				  /// Time between current frame and last frame
			float lastFrame = 0.0f; 			  /// Time of last frame

			sol::state lua; 				/// provides an instance of the lua state

			std::vector<MD2_TEST*> MD2models;

		

				/******************************************************************************************************************************************
				 * @brief  : init()
				 * @brief  : initialise all the objects we need for the game engine to work
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
			
			void init();


				/******************************************************************************************************************************************
				 * @brief  : run()
				 * @brief  : used to run the game engine is called from main
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			void run();


				/******************************************************************************************************************************************
				 * @brief  : cleanUp()
				 * @brief  : used to cleanUp the game engine once everything has closed
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			void cleanUp();


				/******************************************************************************************************************************************
				 * @brief  : getInstance()
				 * @brief  : provides an instance of the game engine
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			static LabEngine& getInstance();

			
			//std::unique_ptr<GUI> engGUI;
			bool show_demo_window = true; /// JUST FOR TESTING, WILL REMOVE SOON AND PUT IN ITS OWN CLASS
			bool show_image = false; 	 /// SAME AS THE BOOL ABOVE, GOTTA MOVE THIS


			//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);


		private:


				/******************************************************************************************************************************************
				 * @brief  : LabEngine()
				 * @brief  : provides a basic constructor to the LabEngine class
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			// constructor
			LabEngine();


				/******************************************************************************************************************************************
				 * @brief  : LabEngine()
				 * @brief  : provides a basic destructor for the LabEngine class
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			~LabEngine();


				/******************************************************************************************************************************************
				 * @brief  : LabEngine(const LabEngine&)
				 * @brief  : used to delete the copy assignment operator  + assignment
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		

			LabEngine(const LabEngine&) = delete;

			
				/******************************************************************************************************************************************
				 * @brief  : operator=(const LabEngine&)
				 * @brief  : used to provide a const copy of the labengine 
				 * 
				 * @return : void
				 ******************************************************************************************************************************************/
		
			LabEngine& operator=(const LabEngine&) = delete;

			
				/******************************************************************************************************************************************
				 * @brief  : LabEngine* static object 
				 * @brief  : Static object of the lab engine
				 ******************************************************************************************************************************************/
		
			static LabEngine* staticInstance;


	};
//}
