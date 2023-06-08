#pragma once

#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture.h"
#include "Shader.h"

/**
 * @brief Class representing a skybox in a 3D scene.
 */
class Skybox
{
public:
	/**
	 * @brief Default constructor for Skybox.
	 */
	Skybox();

	/**
	 * @brief Loads the cubemap textures for the skybox.
	 *
	 * @param faces A vector of file paths to the 6 cubemap textures in the following order: right, left, top, bottom, front, back.
	 */
	void loadCubemap(std::vector<std::string> faces);

	/**
	 * @brief Renders the skybox using the provided shader, view matrix, and projection matrix.
	 *
	 * @param shader The shader to use for rendering the skybox.
	 * @param view The view matrix.
	 * @param projection The projection matrix.
	 */
	void Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
	std::unique_ptr<Shader> skyboxShader; /**< The shader used for rendering the skybox. */
	std::unique_ptr<Texture> texture; /**< The texture representing the skybox. */
	std::string cubeMapFileNames; /**< File names of the cubemap textures. */

	bool m_cubeMapLoaded; /**< Flag indicating whether the cubemap textures are loaded. */

	unsigned int VBO, VAO; /**< Vertex buffer object (VBO) and vertex array object (VAO) for rendering the skybox. */
	std::vector<float> skyboxVertices; /**< Vertices of the skybox model. */
};
