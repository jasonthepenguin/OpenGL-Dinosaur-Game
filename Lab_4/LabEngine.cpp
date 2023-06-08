#include "LabEngine.h"

#include "singleton.h"


//using Lab::LabEngine;


// our static instance of the lab engine
LabEngine* LabEngine::staticInstance = nullptr;


const int WIDTH  = 1400;
const int HEIGHT = 1080;


void LabEngine::init()
{
	srand(static_cast<unsigned int>(time(0)));

	ourGameData.score = 0;

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

	physController = new PhysicsController;

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

void LabEngine::loadNPCs()
{
	lua.script_file("Lua/NPC.lua");

	sol::table npcTable = lua["NPCs"];

	glm::vec3 pos;

	bool md2 = false;
	std::string md2Path;
	std::string md2texure;

	for (size_t i = 1; i <= npcTable.size(); ++i)
	{
		sol::table npc = npcTable[i];

		pos.x = npc["startPos"]["x"];
		pos.y = npc["startPos"]["y"];
		pos.z = npc["startPos"]["z"];

		float scaleX = npc["scale"]["x"];
		float scaleY = npc["scale"]["y"];
		float scaleZ = npc["scale"]["z"];

		bool md2 = npc["md2"].get_or(false);

		std::string md2Path = npc["md2Path"].get_or(std::string(""));
		std::string md2texture = npc["md2texture"].get_or(std::string(""));

		//NPC newNPC(posX, posY, posZ, scaleX, scaleY, scaleZ, md2, md2Path, md2texture);
		NPC* newNPC = new NPC;
		newNPC->position = pos;
		newNPC->spawnPoint = pos;
		newNPC->loadMD2Model((char*)md2Path.c_str(), (char*)md2texture.c_str());
		
		gameObjects.push_back(newNPC);
		entityMgr.registerEntity(newNPC);
		//npcList.push_back(newNPC);

	}
	
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


void LabEngine::setupLuaAI()
{
	lua.script_file("Lua/AI/States.lua");

	lua.new_usertype<NPC>("NPC",
		"playAnimation", &NPC::playAnimation,
		"distanceToPlayer", &NPC::distanceToPlayer,
		"lookAtplayer", &NPC::lookAtplayer,
		"moveToPlayer", &NPC::moveToPlayer,
		"chooseRandomDirection", &NPC::chooseRandomDirection,
		"wander", &NPC::wander,
		"ForwardLook", &NPC::ForwardLook,
		"npcFSM", &NPC::npcFSM,
		"getCooldown", &NPC::getCooldown,
		"sendMessage", &NPC::sendMessage,
		"getID", &NPC::getID,
		"findClosestNPC", &NPC::findClosestNPC,
		"setWaypoint", &NPC::setWaypoint,
		"moveToWaypoint", &NPC::moveToWaypoint,
		"distanceToWaypoint", &NPC::distanceToWaypoint,
		"position", &NPC::position
		);
	
	/**/
	lua.new_usertype<telegram>(
		"Telegram",
		"msg", &telegram::msg,
		"extraInfo", &telegram::extraInfo
		);

	lua.new_usertype<glm::vec3>("vec3",
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z
		);


	lua.new_usertype<StateMachine<NPC>>("FSM",
		"changeState", &StateMachine<NPC>::changeState);


	// FSM messaging
	fsmMessage.addValue("COME_HERE_NOW");
	// std::cout << fsmMessage << std::endl;
}

void LabEngine::run()
{





	// Skybox
	setupSkybox();


	Water floorWater;
	floorWater.init();
	floorWater.setSize(1000.0f);
	floorWater.position.y = 12.0f;
	

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

	loadNPCs();
	setupLuaAI();

	

	// Try and load the tree
	Model tree("models/old_tree/scene.gltf");

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
	
	// basic timer stuff ( probably move this elsewhere, but running out of time :( 
	timeMgr.createTimer("gameEndTimer", 60);
	timeMgr.getTimer("gameEndTimer")->start();


	lastTime = m_window->getTime();

	while (!m_window->shouldClose())
	{
		timeMgr.updateAll();
	
		physController->update(gameObjects);

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
		
		//std::cout << m_camera->getCameraLocation().x << std::endl;
		

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

		// test render of the tree
		//------------------------------------------------------------
		model = glm::mat4(1.0);
		glm::vec3 modelPos = glm::vec3(192.0f, 30.0f, 192.0f);
		model = glm::translate(model, modelPos);
		model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
		ourShader.setMat4("model", model);
		tree.Draw(ourShader);
		//-------------------------------------------------------------


		world->update(deltaTime); // The physics world update and being passed delta time

		//floorWater.position.y = 12.0f;
		floorWater.render(view, projection);

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