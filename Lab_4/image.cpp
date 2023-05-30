
#include "image.h"
#include "stb_image.h"

bool image::loadTextureRaw(std::string filename)
{
	// Load the image
	//unsigned char* image_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);
	image_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);
	if (image_data == NULL) {
		printf("Error loading image: %s\n", stbi_failure_reason());
		return false;

	}
	return true;
}


// get color (x,y)
RGB image::getColor(int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		int index = (y * m_width + x) * m_channels; // calc index of the pixel in the image data

		// get the colour values for the pixel
		unsigned char r = image_data[index + 0];
		unsigned char g = image_data[index + 1];
		unsigned char b = image_data[index + 2];

		// do we need the alpha value?
		unsigned char alpha = m_channels == 4 ? image_data[index + 3] : 255;   // check if number of channels is 4, if so then lets suck that value


		RGB posColour;
		posColour.r = r;
		posColour.g = g;
		posColour.b = b;

		return posColour;


	}
}

// getWidth()  return width
int image::getWidth() {
	return m_width;
}
// getHeight() return height
int image::getHeight() {
	return m_height;
}