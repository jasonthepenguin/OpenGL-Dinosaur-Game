#pragma once

#include "stb_image.h"
#include <glad/glad.h>

#include <string>
#include <iostream>
#include <memory>

class Texture {

public:


	//Texture(std::string filename) : fileName(filename) {}

	virtual void load() = 0;
	

	virtual void bindTexture(int textureUnit) = 0;

	virtual void unbind() = 0;



	unsigned int texture;
	int width;
	int height;

	bool flip = true;

protected:

	std::string fileName;
	//unsigned int texture;
	unsigned char* data;
	//int width;
	//int height;
	int nrChannels;



};




	/***********************************************************
	 * @class   : OpenGLTexture
	 * @brief   : A class used for managing OpenGLTextures
	 * 
	 * @author  : Jason 
 	 * @date    : April 2023
	 * @version : 1.0
	 **********************************************************/

class OpenGLTexture : public Texture {

public:

		/***********************************************************
		 * @brief : OpenGLTexture Constructor
		 * @brief : OpenGLTexture constructor that takes the filename of the texture
		 * 
		 * @param : fileName std::string
		 **********************************************************/
	
	OpenGLTexture(std::string filename) {
		fileName = filename;
	}

	OpenGLTexture()
	{

	}


	void setFileName(const char* textureFileName) {
		fileName = textureFileName;
	}

	void setFileName(std::string textureFileName) {
		fileName = textureFileName;
	}


	virtual void load() override
	{
		glGenTextures(1, &texture); // generating texture ID, creating "1" texture

		// This would need to check for type of image file, etc.... ( Probably have some textre factory creator/manager in the future? )
		glBindTexture(GL_TEXTURE_2D, texture); // binding it so subsequent code will configure this bound texture

		// setting the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//stbi_set_flip_vertically_on_load(true);
		stbi_set_flip_vertically_on_load(flip);
		data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);





		if (data)
		{

			GLenum format;
			if (nrChannels == 1)
			{
				format = GL_RED;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannels == 4)
			{
				format = GL_RGBA;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture!" << std::endl;

		}

		// free the image memory
		stbi_image_free(data);

	}



		/***********************************************************
		 * @brief : bindTexture
		 * @brief : used to bind a textrue to an object
		 * 
		 * @param : textureUnit - int
		 **********************************************************/
	
	virtual void bindTexture(int textureUnit) override
	{

		glActiveTexture(GL_TEXTURE0 + textureUnit);   // modify this function in the future to specify which texture unit? eg 0, 1 ..
		glBindTexture(GL_TEXTURE_2D, texture);
	}


		/***********************************************************
		 * @brief : unbind
		 * @brief : used to unbind a textrue from an object
		 **********************************************************/
	
	virtual void unbind() override
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};




	/***********************************************************
	 * @class   : JpegTexture 
	 * @brief   : A class utilized to load a jpg texture onto a game object
	 * @author  : Jason
	 * @date    : April 2023  
	 * @version : 1.0
	 **********************************************************/

class JpegTexture : public Texture {

public:

		/***********************************************************
		 * @brief : JpegTexture Constructor
		 * @brief : takes the file name of the jpegTexture to bind
		 * @param : std::string fileName
		 **********************************************************/
	
	JpegTexture(std::string filename) {
		fileName = filename;
	}


		/***********************************************************
		 * @brief : load
		 * @brief : overrides the base load and loads the jpeg texture 
		 **********************************************************/
	
	virtual void load() override
	{
		glGenTextures(1, &texture); // generating texture ID, creating "1" texture

		// This would need to check for type of image file, etc.... ( Probably have some textre factory creator/manager in the future? )
		glBindTexture(GL_TEXTURE_2D, texture); // binding it so subsequent code will configure this bound texture

		// setting the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);




		if (data)
		{

			GLenum format;
			if (nrChannels == 1)
			{
				format = GL_RED;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannels == 4)
			{
				format = GL_RGBA;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture!" << std::endl;
		}

		// free the image memory
		stbi_image_free(data);

	}


		/***********************************************************
		 * @brief : bindTexture
		 * @brief : overrides the base bindTexture and binds the jpeg texture 
		 **********************************************************/
	
	virtual void bindTexture(int textureUnit) override
	{

		glActiveTexture(GL_TEXTURE0 + textureUnit);   // modify this function in the future to specify which texture unit? eg 0, 1 ..
		glBindTexture(GL_TEXTURE_2D, texture);
	}


		/***********************************************************
		 * @brief : unbind
		 * @brief : overrides the base unbind and unbinds the jpeg texture 
		 **********************************************************/
	
	virtual void unbind() override
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};





class PngTexture : public Texture {

public:

		/***********************************************************
		 * @brief : PngTexture Constructor
		 * @brief : takes the fileName of the texture
		 * @param : fileName - std::string
		 **********************************************************/
	
	PngTexture(std::string filename) {
		fileName = filename;
	}


		/***********************************************************
		 * @brief : load
		 * @brief : overrides the base load and loads the png texture 
		 **********************************************************/
	
	virtual void load() override
	{
		glGenTextures(1, &texture); // generating texture ID, creating "1" texture

		// This would need to check for type of image file, etc.... ( Probably have some textre factory creator/manager in the future? )
		glBindTexture(GL_TEXTURE_2D, texture); // binding it so subsequent code will configure this bound texture

		// setting the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

		



		if (data)
		{

			GLenum format;
			if (nrChannels == 1)
			{
				format = GL_RED;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannels == 4)
			{
				format = GL_RGBA;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture!" << std::endl;
		}

		// free the image memory
		stbi_image_free(data);

	}


		/***********************************************************
		 * @brief : bindTexture
		 * @brief : overrides the base bindTexture and binds the png texture 
		 * @param : textureUnit - int
		 **********************************************************/
	
	virtual void bindTexture(int textureUnit) override
	{

		glActiveTexture(GL_TEXTURE0 + textureUnit);   // modify this function in the future to specify which texture unit? eg 0, 1 ..
		glBindTexture(GL_TEXTURE_2D, texture);
	}



		/***********************************************************
		 * @brief : unbind
		 * @brief : overrides the base unbind and unbinds the png texture 
		 **********************************************************/
	
	virtual void unbind() override
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};



class TextureFactory {

public:

	std::unique_ptr<Texture> createTexture(std::string fileName) {
		// find out the file type
		std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
		if (extension == "jpg" || extension == "jpeg")
		{
			//return std::make_unique<JpegTexture>(fileName); // unique pointer so when goes out of scope memory is auto deletd. ( I think )
			return std::make_unique<OpenGLTexture>(fileName);
			// CHANGE THIS LATER
			
		}
		else if (extension == "png")
		{
			//return std::make_unique<PngTexture>(fileName); 
			return std::make_unique<OpenGLTexture>(fileName);
			// CHANGE THIS LATER
		}
	}


};