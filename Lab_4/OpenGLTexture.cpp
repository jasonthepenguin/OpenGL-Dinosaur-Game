#include "Texture.h"



OpenGLTexture::OpenGLTexture(std::string filename, TextureType type = TextureType::TEXTURE_2D) : Texture(filename, type) 
{

}


OpenGLTexture::OpenGLTexture() : Texture("", TextureType::TEXTURE_2D)
{

}

OpenGLTexture::OpenGLTexture(unsigned char* img_data, int img_width, int img_height) : Texture("", TextureType::TEXTURE_2D)
{

    if (img_data == nullptr)
    {
        std::cout << "TEXTURE ATTEMPED TO BE CREATED WITH LIKE LITERALLY NOTHING :(" << std::endl;
    }

    data = img_data; // i should be checking if img_data is not null
    width = img_width;
    height = img_height;

    numChannels = 3;
}



void OpenGLTexture::setFileName(const char* textureFileName) 
{
	fileName = textureFileName;
}



void OpenGLTexture::setFileName(std::string textureFileName)
{
	fileName = textureFileName;
}



void OpenGLTexture::setCubemapFileNames(const std::vector<std::string>& fileNames)
{
	cubeMapFileNames = fileNames;
}

std::string OpenGLTexture::getTextureType()
{
    if (textureType == TextureType::TEXTURE_CUBE_MAP)
    {
        return "CUBE_MAP";
    }
    else
    {
        return "TEXTURE_2D";
    }
}

void OpenGLTexture::load()
{

    GLenum target = textureType == TextureType::TEXTURE_CUBE_MAP ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
    GLenum format;
    glGenTextures(1, &texture);
    glBindTexture(target, texture);

    if (data == nullptr) {

        if (textureType == TextureType::TEXTURE_2D)
        {
            glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


            stbi_set_flip_vertically_on_load(flip);
            data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
            if (data)
            {
                if (numChannels == 4)
                {
                    format = GL_RGBA;
                }

                else if (numChannels == 3)
                {
                    format = GL_RGB;
                }

                else if (numChannels == 1)
                {
                    format = GL_RED;
                }

                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                //  if (textureType == TextureType::TEXTURE_2D)

                std::cout << "ERROR TEXTURE CAN NOT LOAD!" << std::endl;
            }
        }

        else if (textureType == TextureType::TEXTURE_CUBE_MAP)
        {
            glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


            for (unsigned int i = 0; i < cubeMapFileNames.size(); ++i)
            {

                data = stbi_load(cubeMapFileNames[i].c_str(), &width, &height, &numChannels, 0);


                if (data == nullptr)
                {
                    std::cout << "ERROR TEXTURE LOAD FAILURE at " << cubeMapFileNames[i] << std::endl;

                    continue;
                }

                if (numChannels == 4)
                {
                    format = GL_RGBA;
                }
                else if (numChannels == 3)
                {
                    format = GL_RGB;
                }
                else if (numChannels == 1)
                {
                    format = GL_RED;
                }
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

                stbi_image_free(data);

                data = nullptr;
            }
        }

    }
    else { // when we already have the data loaded ( eg terrain texture being procedurally generated in program )

        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        format = GL_RGB;

        glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(target);



    }

        stbi_image_free(data);
}


void OpenGLTexture::bindTexture(int textureUnit)
{

	glActiveTexture(GL_TEXTURE0 + textureUnit);   

	GLenum target = GL_TEXTURE_2D;


	if (textureType == TextureType::TEXTURE_CUBE_MAP)
	{
		target = GL_TEXTURE_CUBE_MAP;
	}

	glBindTexture(target, texture);
}


void OpenGLTexture::unbind()
{
	GLenum target = GL_TEXTURE_2D;


	if (textureType == TextureType::TEXTURE_CUBE_MAP)
	{
		target = GL_TEXTURE_CUBE_MAP;
	}

	glBindTexture(target, 0);
}