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


	// creating cubemap

	// loading cubemap
    void loadCubemap(std::vector<std::string> faces)
    {


        TextureFactory tf;
        tf.setTextureType(TextureType::TEXTURE_CUBE_MAP);
        auto texture = tf.createTexture();

        texture->setCubemapFileNames(faces);
        texture->load();
        
    }




};

