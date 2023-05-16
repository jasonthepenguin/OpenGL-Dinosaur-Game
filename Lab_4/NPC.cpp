
#include "NPC.h"



void NPC::Update(float deltaTime)
{
	// update physics 
}

void NPC::Render(Shader& ourShader)
{


	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 modelPos = position;
	//smileyBox.cubePosition = glm::vec3(startX * simpleTerrain->scaleX, startY + 1.0, startZ * simpleTerrain->scaleZ - 5.0f); // using this to show the middle of the terrain roughly
	model = glm::translate(model, modelPos); // translate it down so it's at the center of the scene
	model = glm::scale(model, size);	// it's a bit too big for our scene, so scale it down
	ourShader.setMat4("model", model);


	// draw the 3d model
	ourModel->Draw(ourShader);

}

void NPC::Init()
{
	if (filepath != "null") // set the filepath first before calling Init(), guessing Lua will load this in
	{
		ourModel = new Model(filepath);
	}

}