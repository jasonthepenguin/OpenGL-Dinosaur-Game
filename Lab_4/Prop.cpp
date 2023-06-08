#include "Prop.h"

void Prop::Update(float deltaTime)
{
    // Implement update logic here
}

void Prop::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
    // Implement rendering logic here

	/*
	model = glm::mat4(1.0);
	glm::vec3 modelPos = glm::vec3(192.0f, 30.0f, 192.0f);
	model = glm::translate(model, modelPos);
	model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
	ourShader.setMat4("model", model);
	tree.Draw(ourShader);
	*/

	



	// adjust npc height to terrain floor
	float scaleOffSetX = 1 / LabEngine::getInstance().simpleTerrain->scaleX;
	float scaleOffSetZ = 1 / LabEngine::getInstance().simpleTerrain->scaleZ;
	float newY = 0.0f;





	for (auto new_position : positionList)
	{

		shader.use();

		glm::mat4 model(1.0);

		newY = LabEngine::getInstance().simpleTerrain->getHeight((int)new_position.x * scaleOffSetX, (int)new_position.z * scaleOffSetZ);
		new_position.y += newY;

		model = glm::translate(model, new_position);
		model = glm::scale(model, size);

		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		propModel->Draw(shader);

	}
}

void Prop::Init()
{
    // Implement initialization logic here


	propModel = new Model(modelFilePath.c_str());
}


