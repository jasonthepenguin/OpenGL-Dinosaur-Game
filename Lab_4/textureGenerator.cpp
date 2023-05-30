#include "TextureGenerator.h"




// include singletons if needed


#include <iostream>

textureGenerator::textureGenerator()
{
	for (int i = 0; i < 4; i++)
	{
		tex[i] = NULL;
		numTextures = 0;
		newTex = 0;
		newTexWidth = 0;
		newTexHeight = 0;
		newTexBPP = 3; // 24 bits
	}
}

textureGenerator::~textureGenerator()
{
	delete newTex;
	for (int i = 0; i < 4; i++)
	{
		delete tex[i];
	}
}

bool textureGenerator::addTexture(const char* filename)
{
	if (numTextures < 4)
	{
		numTextures++;
		// loads texture from file - NO OPENGL SETUP YET
		image* newImage = new image;

		//std::unique_ptr<image> newImage = std::make_unique<image>();

		bool loaded = newImage->loadTextureRaw(filename);
		tex[numTextures - 1] = newImage;

		return loaded;
	}
}

int textureGenerator::getNumTextures()
{
	return numTextures;
}

bool textureGenerator::isLoaded(int index)
{
	if (index < 4 && index >= 1)
	{
		return(tex[index] != NULL);
	}
	return false;
}


RGB textureGenerator::getColor(int texNum, int x, int y)
{
	RGB val;
	val.r = 0;
	val.g = 0;
	val.b = 0;

	if (texNum > 3 || texNum < 0)
	{
		return val;
	}
	return tex[texNum]->getColor(x, y);

}

bool textureGenerator::setupNewTexture(int width, int height)
{
	// to add - ensure power of 2
	newTexHeight = height;
	newTexWidth = width;
	newTex = new unsigned char[newTexHeight * newTexWidth * newTexBPP];

	if (!newTex)
	{
		return false;
	}
	return true;
}

void textureGenerator::setColor(int x, int y, RGB color)
{
	if ((x < newTexWidth) && (y < newTexHeight))
	{
		/*
		newTex[((y * newTexHeight) + x) * newTexBPP] = color.r;
		newTex[((y * newTexHeight) + x) * newTexBPP + 1] = color.g;
		newTex[((y * newTexHeight) + x) * newTexBPP + 2] = color.b;
		*/
		newTex[((y * newTexWidth) + x) * newTexBPP] = color.r;
		newTex[((y * newTexWidth) + x) * newTexBPP + 1] = color.g;
		newTex[((y * newTexWidth) + x) * newTexBPP + 2] = color.b;
	}
}

float textureGenerator::getRange()
{
	if (numTextures > 0) {
		return 255.0 / (float)numTextures;
	}
	return 0.0;
}

float textureGenerator::getTextureMax(int texNum)
{
	if (texNum > numTextures - 1)
		return 0.0;
	else
		return((255.0 / (float)numTextures) * (texNum + 1));
}

unsigned int textureGenerator::getTexWidth(int texNo)
{
	if (texNo > 0 && texNo < numTextures)
		return tex[texNo]->getWidth();
	return -1;
}

unsigned int textureGenerator::getTexHeight(int texNo)
{
	if (texNo > 0 && texNo < numTextures)
		return tex[texNo]->getHeight();
	return -1;
}


