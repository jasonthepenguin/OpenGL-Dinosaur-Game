#pragma once


#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture.h"
#include "Shader.h"

class Skybox 
{


public:

	Skybox();

	void loadCubemap(std::vector<std::string> faces); // pass 6 image files for the cubemap

	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
	
	

private:
	
	std::unique_ptr<Shader> skyboxShader;
	std::unique_ptr<Texture> texture;
	std::string cubeMapFileNames;

	bool m_cubeMapLoaded;

	unsigned int VBO, VAO;
	std::vector<float> skyboxVertices;
	

};

