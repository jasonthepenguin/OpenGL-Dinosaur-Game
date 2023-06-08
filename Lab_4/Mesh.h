#pragma once

// Soon replace with Graphics
#include <glad/glad.h>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "Shader.h"

#include <vector>

/**
 * @brief Struct representing vertex attributes for each vertex.
 */
struct Vertex
{
	glm::vec3 Position; /**< Position of the vertex. */
	glm::vec3 Normal; /**< Normal vector of the vertex. */
	glm::vec2 TexCoords; /**< Texture coordinates of the vertex. */
};

/**
 * @brief Struct representing a texture with its ID, type, and path.
 */
struct m_Texture
{
	unsigned int id; /**< ID of the texture. */
	std::string type; /**< Type of the texture (e.g., diffuse or specular). */
	std::string path; /**< Path to the texture file. */
};

/**
 * @brief Class representing a mesh composed of vertices, indices, and textures.
 */
class Mesh
{
public:
	// Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<m_Texture> textures;

	/**
	 * @brief Constructs a Mesh object.
	 * @param vertices The vector of vertices.
	 * @param indices The vector of indices.
	 * @param textures The vector of textures.
	 */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<m_Texture> textures);

	/**
	 * @brief Draws the mesh using a shader.
	 * @param shader The shader to use for rendering.
	 */
	void Draw(Shader& shader);

private:
	unsigned int VAO; /**< Vertex Array Object ID. */
	unsigned int VBO; /**< Vertex Buffer Object ID. */
	unsigned int EBO; /**< Element Buffer Object ID. */

	/**
	 * @brief Sets up the mesh by generating and binding the vertex array and buffer objects.
	 */
	void setupMesh();
};
