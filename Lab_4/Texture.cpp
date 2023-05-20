#include "Texture.h"


Texture::Texture() : 
	texture(0), 
	width(0), 
	height(0), 
	flip(true), 
	data(nullptr), 
	numChannels(0), 
	textureType(TextureType::TEXTURE_2D)
{

}


Texture::Texture(std::string filename, TextureType type) : fileName(filename), textureType(type) 
	
{

}
