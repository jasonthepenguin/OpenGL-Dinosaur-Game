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

// vertex attributes for each vertex
struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

// Store the ID of the texture and its type ( eg diffuse or specular )
struct m_Texture 
{
	unsigned int id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};


class Mesh
{
	public:
		// Mesh data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<m_Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<m_Texture> textures);


		void Draw(Shader& shader);


	private:
		// render data
		unsigned int VAO, VBO, EBO;

		void setupMesh();
};


