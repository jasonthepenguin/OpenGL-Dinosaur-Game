#pragma once


#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture.h"

class Skybox
{
private:
	void loadCubemap(std::vector<std::string> faces);
};

