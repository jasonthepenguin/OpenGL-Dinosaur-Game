#pragma once

#include "stb_image.h"

#include <string>

#include "image.h"

#include <memory>



class textureGenerator
{



public:

	textureGenerator();
	~textureGenerator();

	bool addTexture(const char* filename);
	int getNumTextures();
	bool isLoaded(int index);
	RGB getColor(int texNum, int x, int y);

	bool setupNewTexture(int width, int height);
	void setColor(int x, int y, RGB color);
	unsigned char* getTex() { return newTex; }

	float getRange();
	float getTextureMax(int texNum);

	unsigned int getTexWidth(int texNo);
	unsigned int getTexHeight(int texNo);


	int getNewTexHeight()
	{
		return newTexHeight;
	}
	int getNewTexWidth()
	{
		return newTexWidth;
	}


private:
	image* tex[4];
	unsigned char* newTex;

	int newTexWidth;
	int newTexHeight;
	int newTexBPP; // bytes per pixel
	int numTextures;

};

