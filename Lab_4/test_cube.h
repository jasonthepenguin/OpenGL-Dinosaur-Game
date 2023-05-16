#pragma once


// Soon replace with Graphics
#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"
#include <memory>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>


#include <vector>


#include "GameObject.h"

#include "LabEngine.h"



// physics/collision detection
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;



class test_cube : public GameObject {

public:


	unsigned int VBO, VAO, EBO;

	//glm::vec3 cubePosition;
	glm::mat4 rotationMatrix4x4; // testing collision rotations with this


	// PHYSICS VARIABLES

	// Create a rigid body in the world
	//-------------------------------------------------------------------------------------------------

	// Create a rigid body in the world
	RigidBody* rigidBody;

	//--------------------------------------------------------------------------


	//Shader& ourShader;
	//Shader* ourShader;
	//Shader ourShader("shaders/light_vs.shader", "shaders/light_fs.shader");

	// IMPLEMENTING THE GAMEOBJECT functions


	void Update(float deltaTime) override; // update physics etc

	void Render(Shader& shader) override; // draw cube to the screen

	void Init() override; // eg init vertex attribs, setup physics


	void initPhysics();



	std::vector<std::shared_ptr<Texture>> boxTextures;



	float vertices[288] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	/*
	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	*/


	void init()
	{

		TextureFactory textFact; // temporarily placing this here.

		std::shared_ptr<Texture> container2 = textFact.createTexture("container2.png");
		container2->load();
		boxTextures.push_back(container2);


		std::shared_ptr<Texture> container2_specular = textFact.createTexture("container2_specular.png");
		container2_specular->load();
		boxTextures.push_back(container2_specular);







		//ourShader.use(); // below we are telling OpenGL which texture unit each shader sampler belongs to 
		//ourShader.setInt("texture1", 0);
		//ourShader.setInt("texture2", 1); // or with the shader class

	}

	//void draw(glm::mat4 projection, glm::mat4 view)
	void draw(Shader& ourShader)
	{

		ourShader.use();

		// potentially set values to the shader here if you need to , eg  "ourShader.setFloat("material.shininess", 32.0f);"

		glm::mat4 model = glm::mat4(1.0f);

		// drawing the test box
		glBindVertexArray(VAO);


		// binding the texuture
		for (int i = 0; i < boxTextures.size(); i++) {
			boxTextures[i]->bindTexture(i);
		}

		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, cubePosition);
		model = glm::translate(model, position);
		//float angle = 20.0f;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = model * rotationMatrix4x4; // apply the rotation calculated from the physics engine

		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//containerTexture->unbind();
		//faceTexture->unbind();

		//container2->unbind();
		for (int i = 0; i < boxTextures.size(); i++) {
			boxTextures[i]->unbind();
		}


		glBindVertexArray(0);


	}

	//test_cube(Shader& s) : ourShader(s) {
	test_cube(){

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		
		// texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		


		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		//---------------------------

	}






private:


};

