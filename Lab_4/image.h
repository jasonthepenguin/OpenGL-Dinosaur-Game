#pragma once


#include <string>


struct RGB
{
	int r;
	int g;
	int b;

	void reset() {
		r = 0;
		g = 0;
		b = 0;
	}

};

class image
{
public:

	int m_width;
	int m_height;
	int m_channels;

	std::string m_filename;

	unsigned char* image_data;

	// load texture raw (filename)

	bool loadTextureRaw(std::string filename);


	// get color (x,y)
	RGB getColor(int x, int y);

	// getWidth()  return width
	int getWidth();


	// getHeight() return height
	int getHeight();



};

