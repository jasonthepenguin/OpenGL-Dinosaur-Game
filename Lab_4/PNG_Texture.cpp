#include "Texture.h"

PngTexture::PngTexture(std::string filename)
{
	fileName = filename;
}




void PngTexture::load()
{
	glGenTextures(1, &texture); // generating texture ID, creating "1" texture
	glBindTexture(GL_TEXTURE_2D, texture); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
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
		std::cout << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data);
}


void PngTexture::bindTexture(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}


void PngTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
