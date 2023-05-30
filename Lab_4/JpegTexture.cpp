#include "Texture.h"


/***********************************************************
 * @brief : JpegTexture Constructor
 * @brief : takes the file name of the jpegTexture to bind
 * @param : std::string fileName
 **********************************************************/

JpegTexture::JpegTexture(std::string filename)
{
	fileName = filename;
}




/***********************************************************
 * @brief : load
 * @brief : overrides the base load and loads the jpeg texture
 **********************************************************/

void JpegTexture::load()
{
	glGenTextures(1, &texture); // generating texture ID, creating "1" texture
	glBindTexture(GL_TEXTURE_2D, texture); // bind it

	// setting the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
	 
	GLenum format;
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
		std::cout << "ERROR FAILED TO LOAD TEXTURE!" << std::endl;
	}

	stbi_image_free(data);
}


/***********************************************************
 * @brief : bindTexture
 * @brief : overrides the base bindTexture and binds the jpeg texture
 **********************************************************/

void JpegTexture::bindTexture(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}


/***********************************************************
 * @brief : unbind
 * @brief : overrides the base unbind and unbinds the jpeg texture
 **********************************************************/

void JpegTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}






















class JpegTexture
{
public:
	JpegTexture(std::string filename)
	{
		fileName = filename;
	}

	void load()
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);

		if (data)
		{
			GLenum format;
			if (numChannels == 4)
				format = GL_RGBA;
			else if (numChannels == 3)
				format = GL_RGB;
			else if (numChannels == 1)
				format = GL_RED;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture!" << std::endl;
		}

		stbi_image_free(data);
	}

	void bindTexture(int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	std::string fileName;
	unsigned int texture;
	int width, height, numChannels;
	unsigned char* data;
};