#include "LabEngine.h"




//using Lab::LabEngine;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void processInput(GLFWwindow* window, float deltaTime, Camera& camera);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// our static instance of the lab engine
LabEngine* LabEngine::staticInstance = nullptr;


void LabEngine::init()
{
	// create the m_PixelsGLFWWindow
	int width = 1200;
	int height = 800;
	
	std::cout << "We are now initialising!!" << std::endl;

	
	m_window = Window::getWindow();
	m_window->init();
	m_window->createWindow(width, height, "Assignment 1");


	// creaing the camera
//	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f)); // camera and its starting position
	m_camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

	lastX = width / 2.0f;
	lastY = width / 2.0f;
	bool firstMouse = true;



	//Keyboard_Input* kb = new Keyboard_Input(m_camera);
	std::shared_ptr<Keyboard_Input> kb = std::make_shared<Keyboard_Input>(m_camera);
	std::shared_ptr<Mouse_Input> mp = std::make_shared<Mouse_Input>();

	userInput = new UI_Manager;

	userInput->setPlayerKeyboard(kb);
	userInput->setPlayerMouse(mp);

	// cursor callback for now
	//glfwSetCursorPosCallback(m_window->m_PixelsGLFWWindow, mouse_callback);
	glfwSetCursorPosCallback(m_window->m_PixelsGLFWWindow, Mouse_Input::static_mouse_callback);
	// testing key callback for now
	//glfwSetKeyCallback(m_window->m_PixelsGLFWWindow, key_callback);
	//-------------------------------------

	// SETTING UP THE GRAPHICS

	Graphics_Factory gf;
	graphics = gf.Create("opengl");
	// Setting up OpenGL with GLAD
	graphics->init();
	graphics->setViewport(0, 0, width, height);
	graphics->enableDepthTest(); // doesn't show vertices not visible to camera (back of object)
	//-------------------------------------
	



	

	// Init physics
	world = physicsCommon.createPhysicsWorld();

	// Init the Lua state
	lua.open_libraries(sol::lib::base);
}

void LabEngine::run()
{
	simpleTerrain = new Terrain();
	// Init the GUI
	gui = new EngGUI();


	std::cout << "The engine runs! For now..." << std::endl;

	TextureFactory textFact; // temporarily placing this here.

	auto& engine = LabEngine::getInstance();

	Shader ourShader("shaders/light_vs.shader", "shaders/light_fs.shader");
	
	// Loading the Terrain data in from a raw file. ( SHOW THIS FIRST ) ( NO TERRAIN GENERATING ALOGIRTHM USED )
	
		std::string fileName = "height128.raw";
		simpleTerrain->loadHeightfield(fileName.c_str(), 128); // 128 represents 1.28 km sqaured
		//simpleTerrain->setScalingFactor(0.5, 0.1, 0.50);
		simpleTerrain->setScalingFactor(1.0, 0.1, 1.0);
		// With texture
			simpleTerrain->setUpTerrainData(true);
			simpleTerrain->loadTerrainTexture("grass.jpg");
			simpleTerrain->sharedShader = &ourShader;			// just testing to see if sharing this shader works

	//--------------------------------------------------------------------------------------------------------------------------------------------
			// Loading the Terrain data in dynamically using the fault formation algorithm.  ( SHOW THIS SECOND )
	//-------------------------------------------- ( LOOK AT BOTTOM OF CLASS FOR EXAMPLE CODE OF SHOWING OFF OTHER TERRAIN OPTIONS )---------
			// STARTING POS OF THE TERRAIN
			simpleTerrain->startPos = glm::vec3(0.0, 0.0, 0.0);  // (TODO) change to use GameObjects position member variable



	//------------- ( INIT CAMERA POSITION ) ---------------------- //


			float startX = ((float)simpleTerrain->size / 2.0);
			float startZ = ((float)simpleTerrain->size / 2.0);

			float startY = simpleTerrain->getHeight(startX, startZ);

			std::cout << "Start X : " << startX << ", Start Y : " << startY << " , start Z : " << startZ << std::endl;

			//m_camera->Position = glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ);
			m_camera->setCameraLocation(glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ));

			glm::vec3 lightPosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ);

	


	//------------------------------------------- Vertex Data  + Textures
	
	sol::protected_function_result result = lua.script_file("Lua/testBox.lua", sol::script_pass_on_error);
	if (!result.valid()) {
		sol::error err = result;
		std::cerr << "Failed to execute the Lua script: " << err.what() << std::endl;
		
	}

	sol::table testBoxTable = result;

	
	// Iterate through the array and store the NPC data in a C++ vector
	for (const auto& entry : testBoxTable) {
		sol::table boxTable = entry.second.as<sol::table>();
		sol::table startPosTable = boxTable["startPos"];

		test_cube* cubeData = new test_cube();

		cubeData->position.x = startPosTable["x"];
		cubeData->position.y = startPosTable["y"];
		cubeData->position.z = startPosTable["z"];


		cubeData->position.x = cubeData->position.x + (startX * simpleTerrain->scaleX);
		cubeData->position.y = cubeData->position.y + (startY);
		cubeData->position.z = cubeData->position.z + (startZ * simpleTerrain->scaleZ);

		gameObjects.push_back(cubeData);

		std::cout << "GameObject created!  xyz = " << cubeData->position.x << "," << cubeData->position.y
			<< "," << cubeData->position.z << std::endl;
	}


	result = lua.script_file("Lua/NPC.lua", sol::script_pass_on_error);
	if (!result.valid()) {
		sol::error err = result;
		std::cerr << "Failed to execute the Lua script: " << err.what() << std::endl;

	}

	sol::table NPCTable = result;
	
	//------------------
	
	// INITIAL TESTING
	
	// SETTING UP ALL THE SHADER VALUES USED ( which could be changed for each individual object when drawing if wanted i guess )
	ourShader.use();

	// setting up spotLight
	ourShader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
	ourShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f); // darken diffuse light a bit
	ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

	ourShader.setFloat("spotLight.constant", 1.0f);
	ourShader.setFloat("spotLight.linear", 0.09f);
	ourShader.setFloat("spotLight.quadratic", 0.032f);

	ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
	//---------------------------------------------------------------------------------------------

	// setting up directionalLight
	ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);


	//------------------------------

	ourShader.setInt("material.diffuse", 0); // setting texture the texture units ( texture unit 0 )
	ourShader.setInt("material.specular", 1);


	ourShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	ourShader.setFloat("material.shininess", 32.0f);

//--------------------------------

	// TASK 1, 2 and 3 for lab 7

	MD2_TEST raptor;
	MD2_TEST raptor_weapon;

	raptor.ReadMD2Model((char*)"md2/raptor/tris.md2", (char*)"md2/raptor/green.jpg");
	raptor.loadData();

	raptor_weapon.ReadMD2Model((char*)"md2/raptor/weapon.md2", (char*)"md2/raptor/weapon.jpg");
	raptor_weapon.loadData();

	//raptor.m_position.x = m_camera->Position.x - 5.0;
	//raptor.m_position.y = m_camera->Position.y + 2.0;
	//raptor.m_position.z = m_camera->Position.z;
	raptor.m_position.x = m_camera->getCameraLocation().x - 5.0;
	raptor.m_position.y = m_camera->getCameraLocation().y + 2.0;
	raptor.m_position.z = m_camera->getCameraLocation().z;


	//raptor_weapon.m_position.x = m_camera->Position.x - 5.0;
	//raptor_weapon.m_position.y = m_camera->Position.y + 2.0;
	//raptor_weapon.m_position.z = m_camera->Position.z;
	raptor_weapon.m_position.x = m_camera->getCameraLocation().x - 5.0;
	raptor_weapon.m_position.y = m_camera->getCameraLocation().y + 2.0;
	raptor_weapon.m_position.z = m_camera->getCameraLocation().z;

	MD2models.push_back(&raptor);
	MD2models.push_back(&raptor_weapon);

	//=========================
	//gameObjects.push_back(smileyBox);
	gameObjects.push_back(simpleTerrain);

	//gameObjects.push_back(ourModel);

	// FOR LOOP TO INIT ALL THE OBJECTS ONCE WE HAVE LOADED THEM FULL OF DETAILS FROM LUA I GUESS
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Init();
	}

	//---------------------------------------
	
	while (!m_window->shouldClose())
	{
		// test render IMGUI
		//----------------------------------------------------- ( BEGIN FRAME )


		// calc deltaTime
		float currentFrame = m_window->getTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// checking what keys have been pressed
		m_window->processInput();
		processInput(m_window->m_PixelsGLFWWindow, deltaTime, *m_camera);


		userInput->m_PlayerKeyboard->readInput(m_window->m_PixelsGLFWWindow, deltaTime);
		
		//------------------ BEGIN  RENDERING ---------------------------------//

		// clearing the buffers
		
		graphics->clearColor(0.38f, 0.47f, 0.65f, 1.0f);
		graphics->clearBuffers();



		// using the shader program by activating it first
		ourShader.use();

		// CREATING the basic MODEL, VIEW and PROJECTION matrices variables
		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);



		float scaleOffSetX = 1 / simpleTerrain->scaleX;
		float scaleOffSetZ = 1 / simpleTerrain->scaleZ;
		float newY = 0.0f;

		// UPDATE POSITION OF EACH MD2 model ( JUST FOR THE LAB TO SEE IF THIS WORKS )
		for (auto mdl : MD2models) {
			newY = simpleTerrain->getHeight((int)mdl->m_position.x * scaleOffSetX, (int)mdl->m_position.z * scaleOffSetZ);
			mdl->m_position.y = newY + 1.0;
		}

		
		if (!m_camera->canFly) {
			//newY = simpleTerrain->getHeight((int)m_camera->Position.x * scaleOffSetX, (int)m_camera->Position.z * scaleOffSetZ);
			//m_camera->Position.y = newY + 1.3;
			newY = simpleTerrain->getHeight((int)m_camera->getCameraLocation().x * scaleOffSetX, (int)m_camera->getCameraLocation().z * scaleOffSetZ);
			m_camera->setCameraLocation(glm::vec3(m_camera->getCameraLocation().x, newY + 1.3, m_camera->getCameraLocation().z));

		}
		

		// setting the MODEL, VIEW and PROJECTION matrices

		view = m_camera->GetViewMatrix();
		ourShader.setMat4("view", view);

		// projection ( initialising the shader object which we are going to share with all the game objects )
		projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		ourShader.setMat4("model", model);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		//-----
		//ourShader.setVec3("lightPos", lightPosition.x, lightPosition.y, lightPosition.z);
	//	ourShader.setVec3("viewPos", m_camera->Position.x, m_camera->Position.y, m_camera->Position.z);
		//ourShader.setVec3("spotLight.position", m_camera->Position.x, m_camera->Position.y, m_camera->Position.z);
		ourShader.setVec3("viewPos", m_camera->getCameraLocation().x, m_camera->getCameraLocation().y, m_camera->getCameraLocation().z);
		ourShader.setVec3("spotLight.position", m_camera->getCameraLocation().x, m_camera->getCameraLocation().y, m_camera->getCameraLocation().z);
		ourShader.setVec3("spotLight.direction", m_camera->getCameraDirection().x, m_camera->getCameraDirection().y, m_camera->getCameraDirection().z);
		//-----

		// RENDERING 
		//----------------------------------------

		world->update(deltaTime); // The physics world update and being passed delta time

		// FOR LOOP TO CALL UPDATE ON EACH OBJECT
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(deltaTime);
		}

		// THE FOR LOOP TO CALL RENDER ON EACH OBJECT
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Render(ourShader);
		}

		// TEST RENDERING THE MD2 object

		//-------------------- ( SECOND IMPLEMENTATION OF MD2 )-------------

		for (auto mds : MD2models) {
			// Now we actually render
			//player_2.Render(view, projection);
			mds->Render(view, projection);

			// call animate and pass deltaTime
			//player_2.Animate(deltaTime);
			mds->Animate(deltaTime);
		}

		float deltaValue = 4.0f * deltaTime;

		for (MD2_TEST* model : MD2models) {
			if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_T) == GLFW_PRESS) {
				model->m_position.z -= deltaValue;
			}
			if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_F) == GLFW_PRESS) {
				model->m_position.x -= deltaValue;
			}
			if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_G) == GLFW_PRESS) {
				model->m_position.z += deltaValue;
			}
			if (glfwGetKey(m_window->m_PixelsGLFWWindow, GLFW_KEY_H) == GLFW_PRESS) {
				model->m_position.x += deltaValue;
			}
		}
		//-------------------------------------------------- COMPLETED DRAWING OF TEST BOXES -------------------------//

		m_window->swapBuffers();
		m_window->pollEvents();
	}
}



void mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn)
{
	auto& app = LabEngine::getInstance();

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (app.firstMouse)
	{
		app.lastX = xpos;
		app.lastY = ypos;
		app.firstMouse = false;
	}

	float xoffset = xpos - app.lastX;
	float yoffset = app.lastY - ypos; // reversed since y-coordinates go from bottom to top

	app.lastX = xpos;
	app.lastY = ypos;

	//app.m_camera->ProcessMouseMovement(xoffset, yoffset);
}


void processInput(GLFWwindow* window, float deltaTime, Camera& camera)
{
	float lookSpeed = 400; // optimise this so not creating a float each time. Perhaps variable in Camera

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {}
		//camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {}
		//camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {}
		//camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {}
		//camera.ProcessKeyboard(RIGHT, deltaTime);


}


/*
// Key callback function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	auto& engRef = LabEngine::getInstance();
	//bool& wireframe = engRef.wireframe;


	// If the "C" key is pressed and the action is key press, toggle the light state
	if (key == GLFW_KEY_K && action == GLFW_PRESS) 
	{
	//	wireframe = !wireframe;
		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{

		for (auto model : engRef.MD2models) 
		{
			model->playNextAnimation();
		}
	}

	
	// If the "F" key is pressed then swap between can FLY and can't FLY
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		engRef.canFly = !engRef.canFly;
		
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) 
	{
		//engRef.show_demo_window = !engRef.show_demo_window;
		engRef.gui->show_demo_window = !engRef.gui->show_demo_window;
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) 
	{
		//engRef.show_image = !engRef.show_image;
		engRef.gui->show_image = !engRef.gui->show_image;
	}

	// reset box location. Just testing this here for now
	if(key == GLFW_KEY_R && action == GLFW_PRESS)
	{

		auto world = engRef.world;

		Vector3 n_position(engRef.m_camera->Position.x, engRef.m_camera->Position.y, engRef.m_camera->Position.z);
		Quaternion orientation = Quaternion::identity();
		Transform transform(n_position, orientation);

		RigidBody* rigidBody = world->createRigidBody(transform);
		BoxShape* boxShape = LabEngine::getInstance().physicsCommon.createBoxShape(Vector3(0.5, 0.5, 0.5));
	
		// Relative transform
		Transform r_transform = Transform::identity();
		// Add the collider to the rigidbody
		Collider* collider;
		collider = rigidBody->addCollider(boxShape, r_transform);

		test_cube* newCube = new test_cube();
		newCube->Init();
		float force = 10.0f;
		rigidBody->setLinearVelocity(Vector3(engRef.m_camera->getCameraDirection().x * force, engRef.m_camera->getCameraDirection().y * force, engRef.m_camera->getCameraDirection().z * force));
		newCube->rigidBody = rigidBody;
		engRef.gameObjects.push_back(newCube);
	}
}
*/

void LabEngine::cleanUp()
{


}

// constructor
LabEngine::LabEngine()
{
	init();

}

// destructor
LabEngine::~LabEngine()
{

}

LabEngine& LabEngine::getInstance()
{
	if (!staticInstance) // checking if an instance has already been created or not
	{
		staticInstance = new LabEngine();
	}
	return *staticInstance;
}