
#include "NPC.h"



void NPC::Update(float deltaTime)
{
	// update physics 

	// update literally anything else etc AI
	// pos of md2 model
	// pos of assimp model

	moveToPlayer();

	// adjust npc height to terrain floor
	float scaleOffSetX = 1 / LabEngine::getInstance().simpleTerrain->scaleX;
	float scaleOffSetZ = 1 / LabEngine::getInstance().simpleTerrain->scaleZ;
	float newY = 0.0f;
	for (auto &mdl : MD2models) {
		newY = LabEngine::getInstance().simpleTerrain->getHeight((int)position.x * scaleOffSetX, (int)position.z * scaleOffSetZ);
		position.y = newY + 1.0;
	}

	for (auto &ourModel : MD2models)
	{
		ourModel->Animate(deltaTime);
		ourModel->m_position = position;
	}

	

	
}

void NPC::Render(Shader& ourShader, const glm::mat4& view, const glm::mat4& projection)
{
	lookAtplayer();


	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 modelPos = position;
	//smileyBox.cubePosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1.0, startZ * simpleTerrain->scaleZ - 5.0f); // using this to show the middle of the terrain roughly


	model = glm::translate(model, modelPos); // translate it down so it's at the center of the scene
	model = glm::scale(model, size);	// it's a bit too big for our scene, so scale it down
	
	ourShader.setMat4("model", model);


	// draw the 3d model
	if (ourModel) {
		ourModel->Draw(ourShader);
	}

	//model *= rotation;
	// draw the md2 model 
	for (auto& ourModel : MD2models)
	{
		
		ourModel->rotationMatrix4x4 = rotation;
		ourModel->Render(view, projection);
	}

}

void NPC::Init()
{
	if (filepath != "null") // set the filepath first before calling Init(), guessing Lua will load this in
	{
		ourModel = new Model(filepath);
	}



}


bool NPC::loadMD2Model(std::string filePath, std::string texturePath)
{
	if (filePath.empty() || texturePath.empty())
	{
		std::cerr << "Failed to load an MD2 model for an NPC!" << std::endl;
		return false;
	}

	MD2models.push_back(std::make_unique<MD2_TEST>()); //adding a new MD2 model 
	MD2models.back()->ReadMD2Model((char*)filePath.c_str(), (char*)texturePath.c_str());
	MD2models.back()->loadData();

	MD2models.back()->m_position = position;
	
}


void NPC::lookAtplayer()
{

	glm::vec3 npcPosition = position; // Set this to your NPC's position
	glm::vec3 playerPosition = LabEngine::getInstance().m_camera->getCameraLocation(); // Set this to your player's position

	// Calculate direction vector
	glm::vec3 direction = glm::normalize(playerPosition - npcPosition);

	// Assuming your NPC initially faces towards the positive Z-axis,
	// we need to calculate the angle between the direction vector and the Z-axis.
	// Since we don't care about the y-axis, we ignore the y-component of the direction vector.
	glm::vec3 directionOnXZPlane = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), directionOnXZPlane, glm::vec3(0.0f, 1.0f, 0.0f));
	//float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), directionOnXZPlane, glm::vec3(0.0f, 0.0f, 1.0f));

	// Now you can use this angle to rotate your NPC around the y-axis.
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

	rotation = rotationMatrix;
	
}

void NPC::playAnimation(std::string animationName)
{
	



	for (auto& ourModel : MD2models)
	{
		for (const auto& mapping : ourModel->animNameMap)
		{
			std::cout << "Animation name: \"" << mapping.first << "\", Cycle index: " << mapping.second << std::endl;
		}
		
		ourModel->currAnimCycle = ourModel->animNameMap[animationName];
	}


}

void NPC::moveToPlayer()
{

	

	glm::vec3 npcPosition = position; // Set this to your NPC's position
	glm::vec3 playerPosition = LabEngine::getInstance().m_camera->getCameraLocation(); // Set this to your player's position

	float lerpFactor = walkingSpeed * LabEngine::getInstance().deltaTime;

	glm::vec3 direction = glm::normalize(playerPosition - npcPosition);

	position += direction * lerpFactor;
	

}
