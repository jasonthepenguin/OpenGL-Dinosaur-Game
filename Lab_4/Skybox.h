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

	void loadCubemap(std::vector<std::string> faces);
	

private:
	
	std::unique_ptr<Shader> skyboxShader;

	bool m_cubeMapLoaded;


};

