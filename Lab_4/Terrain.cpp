#include "Terrain.h"

#include "LabEngine.h"


void Terrain::Update(float deltaTime)
{

}

void Terrain::Render(Shader& shader, const glm::mat4& view, const glm::mat4& projection)
{
	bruteForceRender();
}


void Terrain::Init()
{
	auto world = LabEngine::getInstance().world;
	const int nbVertices = vert_pos.size() / 3;
	std::cout << "num of vert pos : " << nbVertices << std::endl;
	const int nbTriangles = indices.size() / 3;


	TriangleVertexArray* triangleArray = new TriangleVertexArray(nbVertices, vert_pos.data(), 3 * sizeof(float), nbTriangles, indices.data(), 3 * sizeof(int), TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
	TriangleMesh* triangleMesh = LabEngine::getInstance().physicsCommon.createTriangleMesh();
	triangleMesh->addSubpart(triangleArray);
	ConcaveMeshShape* concaveMesh = LabEngine::getInstance().physicsCommon.createConcaveMeshShape(triangleMesh);

	// create a terrain collision
	rp3d::Vector3 MapPos(0.0f, 0.0f, 0.0f);
	rp3d::Quaternion fieldOrientation = rp3d::Quaternion::identity();
	rp3d::Transform fieldTransform(MapPos, fieldOrientation);
	concaveMeshBody = world->createRigidBody(fieldTransform);
	concaveMeshBody->setType(rp3d::BodyType::STATIC); // <-- set  to static

	// add collider
	rp3d::Collider* concaveMeshCollider;
	concaveMeshCollider = concaveMeshBody->addCollider(concaveMesh, rp3d::Transform::identity());
}


// step 2 : load heightfield

bool Terrain::loadHeightfield(const char* filename, const int size)
{
	std::ifstream infile(filename, std::ios::binary);
	if (!infile)
	{
		std::cerr << "Cannot open file! : " << filename << std::endl;
		return false;
	}

	if (terrainData)
	{
		delete[] terrainData;
	}

	if (size > 0)
	{
		terrainData = new unsigned char[size * size];
	}
	if (terrainData == NULL)
	{
		return false;
	}

	infile.seekg(0, std::ios::end);
	int length = infile.tellg();

	// read data as a block
	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char*>(terrainData), length);
	infile.close();
	this->size = size;


	return true;
}



// step 3 : set scaling values
void Terrain::setScalingFactor(float xScale, float yScale, float zScale) {

	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;

}


// step 4 : brute force render
void Terrain::bruteForceRender()
{
	ourShader->use();
	glm::mat4 model = glm::mat4(1.0f);

	if (!hasTexture)
	{
		glBindVertexArray(VAO);
		model = glm::translate(model, startPos);
		ourShader->setMat4("model", model);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{										
		glBindVertexArray(VAO);
		model = glm::translate(model, startPos);
		sharedShader->use();
		sharedShader->setMat4("model", model);
		terrainTexture->bindTexture(0);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		terrainTexture->unbind();
	}
	glBindVertexArray(0);
}



void Terrain::setUpVertexArrayData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



void Terrain::setUpNoTextureAttributes()
{
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}



void Terrain::setUpTexturedAttributes()
{
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}


void Terrain::setupNonTexturedVerts()
{
	unsigned char heightColor;
	for (int zCoord = 0; zCoord < size; zCoord++)
	{
		for (int xCoord = 0; xCoord < size; xCoord++)
		{
			heightColor = getHeightColor(xCoord, zCoord);

			vertices.push_back((float)xCoord * scaleX);
			vertices.push_back(getHeight(xCoord, zCoord));
			vertices.push_back((float)zCoord * scaleZ);
			vertices.push_back((float) heightColor);

			if (xCoord < size - 1 && zCoord < size - 1)
			{
				unsigned int topLeft = zCoord * size + xCoord;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = topLeft + size;
				unsigned int bottomRight = bottomLeft + 1;

				// First triangle
				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);

				// Second triangle
				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}
	}
}


void Terrain::setUpTerrainData(bool hasTexture)
{
	this->hasTexture = hasTexture;

	if (hasTexture == false)
	{
		ourShader = new Shader("shaders/vertexShader_terrain.shader", "shaders/fragmentShader_terrain.shader");
		setUpNoTextureAttributes();
		// step 1) : set up new vertex array
		setupNonTexturedVerts();
		// step 2) : set upVAO and VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		// positionttribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//---------------------------
	}
	else
	{
		// use shaders for textured terrain
		ourShader = new Shader("shaders/vertexShader.shader", "shaders/fragmentShader.shader");
		
		setUpTexturedAttributes();
		unsigned char hcolor;  //color of the height 
		float texLeft;
		float texBottom;
		float texTop;
	
		for (int zCoord = 0; zCoord < size; zCoord++) 
		{
			for (int xCoord = 0; xCoord < size; xCoord++)
			{
				// Create the vertex at (xCoord, zCoord)
				hcolor = getHeightColor(xCoord, zCoord);
				vertices.push_back((float)xCoord * scaleX);
				vertices.push_back(getHeight(xCoord, zCoord));
				vertices.push_back((float)zCoord * scaleZ);
				// just storing the vertex pos separately just to test something ( delete this once done )
				vert_pos.push_back((float)xCoord* scaleX);
				vert_pos.push_back(getHeight(xCoord, zCoord));
				vert_pos.push_back((float)zCoord* scaleZ);
				// Calculate normals
				float currentX = (float)xCoord * scaleX;
				float currentY = getHeight(xCoord, zCoord);
				float currentZ = (float)zCoord * scaleZ;
				float heightLeft = xCoord > 0 ? getHeight(xCoord - 1, zCoord) : currentY;
				float heightRight = xCoord < size - 1 ? getHeight(xCoord + 1, zCoord) : currentY;
				float heightUp = zCoord > 0 ? getHeight(xCoord, zCoord - 1) : currentY;
				float heightDown = zCoord < size - 1 ? getHeight(xCoord, zCoord + 1) : currentY;

				glm::vec3 normal = glm::normalize(glm::vec3( heightLeft - heightRight, 2.0f, heightUp - heightDown));

				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
				//----------------------------------------
				// Add texture coordinates
				texLeft = (float)xCoord / size;
				texBottom = (float)zCoord / size;
				vertices.push_back(texLeft);
				vertices.push_back(texBottom);
				// Only generate indices if NOT at the edge of the terrain data grid
				if (xCoord < size - 1 && zCoord < size - 1) 
				{
					unsigned int topLeft = zCoord * size + xCoord;
					unsigned int topRight = topLeft + 1;
					unsigned int bottomLeft = topLeft + size;
					unsigned int bottomRight = bottomLeft + 1;
					// First triangle
					indices.push_back(topLeft);
					indices.push_back(bottomLeft);
					indices.push_back(topRight);
					// Second triangle
					indices.push_back(topRight);
					indices.push_back(bottomLeft);
					indices.push_back(bottomRight);
				}
			}
		}
		// step 2) set up VAO and VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		glBindVertexArray(0);
		ourShader->use();
		ourShader->setInt("texture1", 0);
	}
	return;
}


void Terrain::loadTerrainTexture(std::string textureName)
{
	TextureFactory textFact; 
	terrainTexture = textFact.createTexture(textureName); // returns unique pointer
	terrainTexture->load();
}


float Terrain::getHeight(int xCoord, int zCoord)
{
	if (xCoord < size && zCoord < size && xCoord >= 0 && zCoord >= 0)
	{
		return ((float)(terrainData[(zCoord * size) + xCoord]) * scaleY);
	}
}


unsigned char Terrain::getHeightColor(int xCoord, int zCoord)
{
	if (xCoord < size && zCoord < size)
	{
		return terrainData[zCoord * size + xCoord];
	}
	return 1;
}


void Terrain::normalizeHeightField()
{
	float fMin = heightData[0];
	float fMax = heightData[0];
	float fHeight;
	int i;

	// find the min and max values of the height terrainData
	for (i = 1; i < size * size; i++)
	{
		if (heightData[i] > fMax)
		{
			fMax = heightData[i];
		}
		else if (heightData[i] < fMin)
		{
			fMin = heightData[i];
		}
	}

	//find the range of the altitude
	if (fMax > fMin)
	{
		fHeight = fMax - fMin;
		for (i = 0; i < size * size; i++)
		{
			terrainData[i] = static_cast<unsigned char>(((heightData[i] - fMin) / fHeight) * 255.0f);
		}
	}
	else
	{
		for (i = 0; i < size * size; i++)
		{
			terrainData[i] = 0;
		}
	}
}


bool Terrain::genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random)
{
	int x1, x2, z1, z2;
	float* heights = NULL;
	int displacement;

	if (hSize <= 0) {
		return false;
	}
	if (random) // create truly random map
	{
		srand(time(NULL));
	}

	size = hSize;
	heights = new float[size * size]; // allocate memory
	terrainData = new unsigned char[size * size];
	if (heights == NULL || terrainData == NULL)
	{
		return false;
	}

	// initialise the heightfield array to all zeros
	for (int i = 0; i < size * size; i++)
	{
		heights[i] = 0.0;
	}

	// generate heightfield
	for (int j = 0; j < iterations; j++) {

		//calculate the displacement value for the current iteration 
		displacement = maxHeight - ((maxHeight - minHeight) * j) / iterations;

		//pick the first random point P1(x1, z1) from the height map 
		x1 = (rand() % size);
		z1 = (rand() % size);

		do
		{
			x2 = (rand() % size);
			z2 = (rand() % size);
		} while (x2 == x1 && z2 == z1);

		//for each point P(xCoord, zCoord) in the field, calculate the new height values 
		for (int z = 0; z < size; z++)
		{
			for (int x = 0; x < size; x++)
			{
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0)
				{
					heights[(z * size) + x] += (float)displacement;
				}
			}
		}
		addFilter(heights, weight);
	}

	// normalise the heightfield
	normaliseTerrain(heights);

	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			terrainData[(z * size) + x] = heights[(z * size) + x];
		}
	}
	delete[] heights;
	return true;
}


void Terrain::addFilter(float* terData, float weight)
{
	for (int itrLR = 0; itrLR < size; itrLR++)
	{
		filterPass(&terData[size * itrLR], 1, weight);
	}

	for (int itrRL = 0; itrRL < size; itrRL++)
	{
		filterPass(&terData[size * itrRL + size - 1], -1, weight);
	}

	for (int itrTB = 0; itrTB < size; itrTB++)
	{
		filterPass(&terData[itrTB], size, weight);
	}

	for (int itrBT = 0; itrBT < size; itrBT++)
	{
		filterPass(&terData[size * (size - 1) + itrBT], -size, weight);
	}
}



void Terrain::filterPass(float* startP, int increment, float weight)
{
	float previousValue = *startP;
	int currentIndex = increment;
	float filterWeight = weight;

	for (int i = 1; i < size; i++)
	{
		*(startP + currentIndex) = filterWeight * previousValue + (1 - filterWeight) * (*(startP + currentIndex));
		previousValue = *(startP + currentIndex);
		currentIndex += increment;
	}
}


void Terrain::normaliseTerrain(float* terData)
{
	float minValue = terData[0];
	float maxValue = terData[0];
	float heightRange;


	for (int i = 1; i < size * size; i++)
	{
		if (terData[i] > maxValue)
		{
			maxValue = terData[i];
		}
		else if (terData[i] < minValue)
		{
			minValue = terData[i];
		}
	}

	// Find the range of the altitude
	if (maxValue <= minValue)
	{
		return;
	}
	heightRange = maxValue - minValue;

	for (int i = 0; i < size * size; i++)
	{
		terData[i] = ((terData[i] - minValue) / heightRange) * 255.0f;
	}
}


/**
//requires the following lib https://github.com/tinyobjloader/tinyobjloader, will load this terrain https://ambientcg.com/view?id=Terrain002.
void Terrain::loadTerrainFromOBJ(const std::string& filename)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

	if (!err.empty())
	{
		std::cerr << "OBJ loading error: " << err << std::endl;
	}

	if (!success)
	{
		std::cerr << "Failed to load OBJ file: " << filename << std::endl;
		return;
	}

	// Store the extracted data in the TinyObjDLoader struct
	TinyObjDLoader objData;
	objData.vertices.clear();
	objData.texcoords.clear();
	objData.normals.clear();
	objData.indices.clear();

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			// Vertex position
			objData.vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
			objData.vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
			objData.vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

			// Texture coordinates
			objData.texcoords.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
			objData.texcoords.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);

			// Normals
			objData.normals.push_back(attrib.normals[3 * index.normal_index + 0]);
			objData.normals.push_back(attrib.normals[3 * index.normal_index + 1]);
			objData.normals.push_back(attrib.normals[3 * index.normal_index + 2]);

			// Indices
			objData.indices.push_back(objData.indices.size());
		}
	}

	// Update the setup and rendering code accordingly
	setUpVertexArrayData(objData);
}
*/