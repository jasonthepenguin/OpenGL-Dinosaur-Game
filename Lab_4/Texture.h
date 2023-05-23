#pragma once

#include "stb_image.h"
#include <glad/glad.h>

#include <string>
#include <vector>
#include <iostream>
#include <memory>


enum class TextureType 
{
	TEXTURE_2D,
	TEXTURE_CUBE_MAP
};


class Texture 
{
	public:

		Texture();
		Texture(std::string filename, TextureType type);


		virtual void load() = 0;
	

		virtual void bindTexture(int textureUnit) = 0;

		virtual void unbind() = 0;

		virtual void setCubemapFileNames(const std::vector<std::string>& fileNames) = 0;


		virtual std::string getTextureType() = 0;

		unsigned int texture; // texture ID 
		int width;
		int height;


		bool flip = true;

	protected:

		std::string fileName;
		unsigned char* data;
		int numChannels;
		TextureType textureType;
		std::vector<std::string> cubeMapFileNames;
};


	/***********************************************************
	 * @class   : OpenGLTexture
	 * @brief   : A class used for managing OpenGLTextures
	 * 
	 * @author  : 
 	 * @date    : April 2023
	 * @version : 1.0
	 **********************************************************/

class OpenGLTexture : public Texture 
{

	public:

		OpenGLTexture();


			/***********************************************************
			 * @brief : OpenGLTexture Constructor
			 * @brief : OpenGLTexture constructor that takes the filename of the texture
			 * 
			 * @param : fileName std::string
			 **********************************************************/
	
		OpenGLTexture(std::string filename, TextureType type);

	
		void setFileName(const char* textureFileName);


		void setFileName(std::string textureFileName);


		virtual void setCubemapFileNames(const std::vector<std::string>& fileNames) override;


		virtual std::string getTextureType() override;

		//void channelCount(int numChannels, GLenum format);


		virtual void load() override;


			/***********************************************************
			 * @brief : bindTexture
			 * @brief : used to bind a textrue to an object
			 * 
			 * @param : textureUnit - int
			 **********************************************************/
	
		virtual void bindTexture(int textureUnit) override;


			/***********************************************************
			 * @brief : unbind
			 * @brief : used to unbind a textrue from an object
			 **********************************************************/
	
		virtual void unbind() override;


	
};




	/***********************************************************
	 * @class   : JpegTexture 
	 * @brief   : A class utilized to load a jpg texture onto a game object
	 * @author  : 
	 * @date    : April 2023  
	 * @version : 1.0
	 **********************************************************/

class JpegTexture : public Texture
{
	public:

		/***********************************************************
		 * @brief : JpegTexture Constructor
		 * @brief : takes the file name of the jpegTexture to bind
		 * @param : std::string fileName
		 **********************************************************/
	
	JpegTexture(std::string filename);


	//void channelCount(int numChannels, GLenum format);


		/***********************************************************
		 * @brief : load
		 * @brief : overrides the base load and loads the jpeg texture 
		 **********************************************************/
	
	virtual void load() override;


		/***********************************************************
		 * @brief : bindTexture
		 * @brief : overrides the base bindTexture and binds the jpeg texture 
		 **********************************************************/
	
	virtual void bindTexture(int textureUnit) override;


		/***********************************************************
		 * @brief : unbind
		 * @brief : overrides the base unbind and unbinds the jpeg texture 
		 **********************************************************/
	
	virtual void unbind() override;


private:

};


class PngTexture : public Texture 
{
	public:

			/***********************************************************
			 * @brief : PngTexture Constructor
			 * @brief : takes the fileName of the texture
			 * @param : fileName - std::string
			 **********************************************************/
	
		PngTexture(std::string filename);



		//void channelCount(int numChannels, GLenum format);


			/***********************************************************
			 * @brief : load
			 * @brief : overrides the base load and loads the png texture 
			 **********************************************************/
	
		virtual void load() override;


			/***********************************************************
			 * @brief : bindTexture
			 * @brief : overrides the base bindTexture and binds the png texture 
			 * @param : textureUnit - int
			 **********************************************************/
	
		virtual void bindTexture(int textureUnit) override;



			/***********************************************************
			 * @brief : unbind
			 * @brief : overrides the base unbind and unbinds the png texture 
			 **********************************************************/
	
		virtual void unbind() override;

		GLenum format;
};



class TextureFactory {

public:


	TextureType type = TextureType::TEXTURE_2D;

	void setTextureType(TextureType textType) {
		type = textType;
	}

	std::unique_ptr<Texture> createTexture(std::string fileName) {
		// find out the file type
		std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
		if (extension == "jpg" || extension == "jpeg")
		{
			//return std::make_unique<JpegTexture>(fileName); // unique pointer so when goes out of scope memory is auto deletd. ( I think )
			return std::make_unique<OpenGLTexture>(fileName, type);
			// CHANGE THIS LATER
			
		}
		else if (extension == "png")
		{
			//return std::make_unique<PngTexture>(fileName); 
			return std::make_unique<OpenGLTexture>(fileName, type);
			// CHANGE THIS LATER
		}
	}

	std::unique_ptr<Texture> createTexture() {

		return std::make_unique<OpenGLTexture>("", type);
		
	}


};