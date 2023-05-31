
#include "NPC.h"



void NPC::Update(float deltaTime)
{
	// update physics 

	// update literally anything else etc AI
	// pos of md2 model
	// pos of assimp model

}

void NPC::Render(Shader& ourShader, const glm::mat4& view, const glm::mat4& projection)
{


	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 modelPos = position;
	//smileyBox.cubePosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1.0, startZ * simpleTerrain->scaleZ - 5.0f); // using this to show the middle of the terrain roughly
	model = glm::translate(model, modelPos); // translate it down so it's at the center of the scene
	model = glm::scale(model, size);	// it's a bit too big for our scene, so scale it down
	ourShader.setMat4("model", model);


	// draw the 3d model
	ourModel->Draw(ourShader);

	// draw the md2 model 

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