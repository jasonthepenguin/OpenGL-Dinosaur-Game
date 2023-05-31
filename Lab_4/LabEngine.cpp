#include "LabEngine.h"




//using Lab::LabEngine;


// our static instance of the lab engine
LabEngine* LabEngine::staticInstance = nullptr;


const int WIDTH  = 1400;
const int HEIGHT = 1080;


void LabEngine::init()
{
	// create the m_PixelsGLFWWindow
	int width = WIDTH;
	int height = HEIGHT;
	
	m_window = Window::getWindow();
	m_window->init();
	m_window->createWindow(width, height, "Assignment 2");
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

	glfwSetCursorPosCallback(m_window->m_PixelsGLFWWindow, Mouse_Input::static_mouse_callback);

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



void LabEngine::setupWorldEnvironment() 
{

	simpleTerrain = new Terrain();

	lua.script_file("Lua/Terrain.lua");

	float startPosX;
	float startPosY;
	float startPosZ;

	float scaleX;
	float scaleY;
	float scaleZ;

	std::string rawFilePath;
	int heightfieldSize;
	bool usesProceduralTexture = false;

	// Get the terrain data
	sol::table terrainsTable = lua["terrain"];
	for (const auto& entry : terrainsTable) {
		sol::table terrain = entry.second.as<sol::table>();

		// Extract terrain data directly into variables
		startPosX = terrain["startPos"]["x"];
		startPosY = terrain["startPos"]["y"];
		startPosZ = terrain["startPos"]["z"];

		scaleX = terrain["scale"]["x"];
		scaleY = terrain["scale"]["y"];
		scaleZ = terrain["scale"]["z"];

		rawFilePath = terrain["rawFilePath"];
		heightfieldSize = terrain["heightfieldSize"];
		usesProceduralTexture = terrain["usesProceduralTexture"];
	}

	simpleTerrain->loadHeightfield(rawFilePath.c_str(), heightfieldSize);
	simpleTerrain->setScalingFactor(scaleX, scaleY, scaleZ);
	simpleTerrain->setUpTerrainData(true);

	// Get the terrain texture paths
	sol::table texturePathsTable = lua["terrainTexturePaths"];
	for (const auto& entry : texturePathsTable) {
		sol::table texturePath = entry.second.as<sol::table>();

		// Extract texture path directly into a variable
		std::string imageFilePath = texturePath["imageFilePath"];
		if (usesProceduralTexture)
		{
			simpleTerrain->addProceduralTexture(imageFilePath.c_str());
		}
		else {
			simpleTerrain->loadTerrainTexture(imageFilePath.c_str());
		}
	}

	if (usesProceduralTexture)
	{
		simpleTerrain->createProceduralTexture();
	}




//	simpleTerrain = new Terrain();
	//gui = new EngGUI();
//	TextureFactory textFact; // temporarily placing this here.
	//auto& engine = LabEngine::getInstance();
	//Shader ourShader("shaders/light_vs.shader", "shaders/light_fs.shader");
}


void LabEngine::setupSkybox()
{
	// Skybox
	skybox = std::make_unique<Skybox>();

	std::vector<std::string> faces;
	lua.script_file("Lua/Skybox.lua");
	sol::table texturePathsTable = lua["SkyBoxTexturePaths"];
	for (const auto& entry : texturePathsTable)
	{
		sol::table texturePath = entry.second.as<sol::table>();
		faces.push_back(texturePath["imageFilePath"].get<std::string>()); // texture path into the faces string vector
	}


	skybox->loadCubemap(faces);




}

/*


void LabEngine::setupPlayerCamera()
{
	float startX = ((float)simpleTerrain->size / 2.0);
	float startZ = ((float)simpleTerrain->size / 2.0);
	float startY = simpleTerrain->getHeight(startX, startZ);
	m_camera->setCameraLocation(glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ));
	glm::vec3 lightPosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ);
}


void LabEngine::loadVertexDataAndTextures() 
{
	Textures.push_back(textFact.loadTexture("images/dirt.png"));
	Textures.push_back(textFact.loadTexture("images/grass.png"));
	Textures.push_back(textFact.loadTexture("images/sand.png"));
	Textures.push_back(textFact.loadTexture("images/snow.png"));
	Textures.push_back(textFact.loadTexture("images/water.png"));
	Textures.push_back(textFact.loadTexture("images/stone.png"));
	Textures.push_back(textFact.loadTexture("images/deepsea.png"));
}

void LabEngine::setupAssetShaders()
{
	// Create shaders
	Shader terrainShader("shaders/terrain_vs.shader", "shaders/terrain_fs.shader");
	Shader waterShader("shaders/water_vs.shader", "shaders/water_fs.shader");
	Shader modelShader("shaders/model_vs.shader", "shaders/model_fs.shader");
	Shader guiShader("shaders/gui_vs.shader", "shaders/gui_fs.shader");
	Shader lightShader("shaders/light_vs.shader", "shaders/light_fs.shader");

	// Bind shaders to their corresponding objects
	// This assumes you have shader member variables in your objects 
	//simpleTerrain->(terrainShader);
	//gui->setShader(guiShader);
	//water->setShader(waterShader);
	//model->setShader(modelShader);
	//light->setShader(lightShader);
}


void LabEngine::setupMD2Models() 
{
	MD2_TEST raptor;
	MD2_TEST raptor_weapon;

	raptor.ReadMD2Model((char*)"md2/raptor/tris.md2", (char*)"md2/raptor/green.jpg");
	raptor.loadData();

	raptor_weapon.ReadMD2Model((char*)"md2/raptor/weapon.md2", (char*)"md2/raptor/weapon.jpg");
	raptor_weapon.loadData();

	raptor.m_position.x = m_camera->getCameraLocation().x - 5.0;
	raptor.m_position.y = m_camera->getCameraLocation().y + 2.0;
	raptor.m_position.z = m_camera->getCameraLocation().z;

	raptor_weapon.m_position.x = m_camera->getCameraLocation().x - 5.0;
	raptor_weapon.m_position.y = m_camera->getCameraLocation().y + 2.0;
	raptor_weapon.m_position.z = m_camera->getCameraLocation().z;

	MD2models.push_back(&raptor);
	MD2models.push_back(&raptor_weapon);
}



void LabEngine::gameLoop() {
	while (!m_window->shouldClose()) {
		// game loop logic goes here
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check for any input
		processInput(m_window->getWindow());

		// Render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set the view and projection matrices here
		// These matrices usually change per frame

		// Render your objects here
		simpleTerrain->draw();
		//water->draw();
		//model->draw();
		//light->draw();

		// Swap buffers
		glfwSwapBuffers(m_window->getWindow());

		// Poll for and process events
		glfwPollEvents();
	}
}




void LabEngine::run() 
{
	setupWorldEnvironment();
	setupPlayerCamera();
	loadVertexDataAndTextures();
	setupAssetShaders();
	setupMD2Models();
	initializeGameObjects();
	gameLoop();
}
*/




void LabEngine::run()
{

	// Skybox
	setupSkybox();
	

	//----------------------------------------
	//simpleTerrain = new Terrain();
	// Init the GUI
	gui = new EngGUI();

	TextureFactory textFact; // temporarily placing this here.
	auto& engine = LabEngine::getInstance();

	Shader ourShader("shaders/light_vs.shader", "shaders/light_fs.shader");
	
	//------------------------------------------------------------------------------

	setupWorldEnvironment();

	simpleTerrain->sharedShader = &ourShader;	
	simpleTerrain->startPos = glm::vec3(0.0, 0.0, 0.0); 


	//------------- ( INIT CAMERA POSITION ) ---------------------- //
	float startX = ((float)simpleTerrain->size / 2.0);
	float startZ = ((float)simpleTerrain->size / 2.0);
	float startY = simpleTerrain->getHeight(startX, startZ);
	m_camera->setCameraLocation(glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ));

	glm::vec3 lightPosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ);

	//------------------------------------------- Vertex Data  + Textures
	sol::protected_function_result result = lua.script_file("Lua/testBox.lua", sol::script_pass_on_error);
	if (!result.valid()) 
	{
		sol::error err = result;
		std::cerr << "Failed to execute the Lua script: " << err.what() << std::endl;
	}

	sol::table testBoxTable = result;

	
	// Iterate through the array and store the NPC data in a C++ vector
	for (const auto& entry : testBoxTable) 
	{
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

		std::cout << "GameObject created!  xyz = " << cubeData->position.x << "," << cubeData->position.y << "," << cubeData->position.z << std::endl;
	}


	result = lua.script_file("Lua/NPC.lua", sol::script_pass_on_error);
	if (!result.valid())
	{
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


	//-------------------------- (NPC Test) No lua, just MD2 testing
	NPC* raptorNPC = new NPC;

	glm::vec3 newPos = m_camera->getCameraLocation();
	newPos.z = newPos.z - 7;
	raptorNPC->position = newPos;
	raptorNPC->loadMD2Model((char*)"md2/raptor/tris.md2", (char*)"md2/raptor/green.jpg");

	raptorNPC->playAnimation("run");

	gameObjects.push_back(raptorNPC);
	

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
		gui->BeginFrame();
		gui->EndFrame();

		// calc deltaTime
		float currentFrame = m_window->getTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// checking what keys have been pressed
		m_window->processInput();


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

		// Either move this to a GameLogic class or into some sort of Player class which is checked upon move() or something
		
		glm::vec3 camXYZ = m_camera->getCameraLocation();
		
		int heightFieldSize = simpleTerrain->size;
		float scaledHeightFieldSizeX = heightFieldSize * simpleTerrain->scaleX;
		float scaledHeightFieldSizeZ = heightFieldSize * simpleTerrain->scaleZ;

		if (camXYZ.x >= scaledHeightFieldSizeX || camXYZ.x <= 0) // checking on the X
		{
			m_camera->setCameraLocation(glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ));
		}
		if (camXYZ.z >= scaledHeightFieldSizeZ || camXYZ.z <= 0) // checking on the Z
		{
			m_camera->setCameraLocation(glm::vec3(startX * simpleTerrain->scaleX, startY + 1, startZ * simpleTerrain->scaleZ));
		}
		//-------------------------------------------------


		
		if (!m_camera->canFly) {
			//newY = simpleTerrain->getHeight((int)m_camera->Position.x * scaleOffSetX, (int)m_camera->Position.z * scaleOffSetZ);
			//m_camera->Position.y = newY + 1.3;
			newY = simpleTerrain->getHeight((int)m_camera->getCameraLocation().x * scaleOffSetX, (int)m_camera->getCameraLocation().z * scaleOffSetZ);
			m_camera->setCameraLocation(glm::vec3(m_camera->getCameraLocation().x, newY + 1.3, m_camera->getCameraLocation().z));

		}
		

		// setting the MODEL, VIEW and PROJECTION matrices

		view = m_camera->GetViewMatrix();

		//----------------------------------------------
		ourShader.setMat4("view", view);

		// projection ( initialising the shader object which we are going to share with all the game objects )
		projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

		ourShader.setMat4("model", model);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		ourShader.setVec3("viewPos", m_camera->getCameraLocation().x, m_camera->getCameraLocation().y, m_camera->getCameraLocation().z);
		ourShader.setVec3("spotLight.position", m_camera->getCameraLocation().x, m_camera->getCameraLocation().y, m_camera->getCameraLocation().z);
		ourShader.setVec3("spotLight.direction", m_camera->getCameraDirection().x, m_camera->getCameraDirection().y, m_camera->getCameraDirection().z);
		//----------------------------------------------------------

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
			gameObjects[i]->Render(ourShader, view, projection);
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


		// DRAWING SKYBOX
		skybox->Render(ourShader, view, projection);

		//-------------------------------------------------- COMPLETED DRAWING OF TEST BOXES -------------------------//
		gui->renderData();
		m_window->swapBuffers();
		m_window->pollEvents();
	}
}




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