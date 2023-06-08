#pragma once


#include <string>


struct RGB
{
    /**
     * @brief Resets the RGB values to zero.
     */
    void reset() {
        r = 0;
        g = 0;
        b = 0;
    }

    int r; /**< Red component */
    int g; /**< Green component */
    int b; /**< Blue component */
};


class image
{
public:

    int m_width; /**< Width of the image */
    int m_height; /**< Height of the image */
    int m_channels; /**< Number of color channels */

    std::string m_filename; /**< Filename of the image */

    unsigned char* image_data; /**< Pointer to the image data */

    /**
     * @brief Loads a texture from a raw file.
     * @param filename The filename of the raw file to load.
     * @return True if the texture was loaded successfully, false otherwise.
     */
    bool loadTextureRaw(std::string filename);

    /**
     * @brief Retrieves the color at the specified coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The RGB color at the specified coordinates.
     */
    RGB getColor(int x, int y);

    /**
     * @brief Returns the width of the image.
     * @return The width of the image.
     */
    int getWidth();

    /**
     * @brief Returns the height of the image.
     * @return The height of the image.
     */
    int getHeight();
};
