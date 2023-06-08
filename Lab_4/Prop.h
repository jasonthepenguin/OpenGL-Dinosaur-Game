#pragma once

#include "GameObject.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>


#include "LabEngine.h"

#include "Model.h"

#include <vector>

class Prop : public GameObject
{
public:


	void Update(float deltaTime) override; // update physics etc

	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) override; // draw cube to the screen

	void Init() override; // eg init vertex attribs, setup physics



	// list of positions this prop can be in ( my cheap and stupid way of saving memory )

	std::vector<glm::vec3> positionList;
	//std::vector<glm::vec3> scaleList;
	std::string modelFilePath;

	Model* propModel;

};

