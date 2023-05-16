#include "Terrain.h"

#include "LabEngine.h"


void Terrain::Update(float deltaTime)
{

}

void Terrain::Render(Shader& shader)
{
	bruteForceRender();
}

void Terrain::Init()
{
	auto world = LabEngine::getInstance().world;


	//const int nbVertices = simpleTerrain->vert_pos.size() / 3;
	const int nbVertices = vert_pos.size() / 3;
	std::cout << "num of vert pos : " << nbVertices << std::endl;


	//const int nbTriangles = simpleTerrain->indices.size() / 3;
	const int nbTriangles = indices.size() / 3;

	//float vertices[3 * nbVertices] = ...;
	//int indices[3 * nbTriangles] = ...;

	TriangleVertexArray* triangleArray =
		//new TriangleVertexArray(nbVertices, simpleTerrain->vert_pos.data(), 3 * sizeof(
		new TriangleVertexArray(nbVertices, vert_pos.data(), 3 * sizeof(
			float), nbTriangles,
			//simpleTerrain->indices.data(), 3 * sizeof(int),
			indices.data(), 3 * sizeof(int),
			TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
			TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

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
bool Terrain::loadHeightfield(const char* filename, const int size) {

	// open for binary read
	std::ifstream infile(filename, std::ios::binary);
	if (!infile) {
		std::cerr << "Cannot open file! : " << filename << std::endl;
		return false;
	}

	// allocate memory
	if (terrainData) {
		delete[] terrainData;
	}
	if (size > 0) {
		terrainData = new unsigned char[size * size];
	}
	if (terrainData == NULL) {
		return false;
	}

	// read in heightfield
		// get length of file
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
void Terrain::bruteForceRender() {

	ourShader->use();


	glm::mat4 model = glm::mat4(1.0f);

	// When not using fault
	//startPos = glm::vec3(-64.0f * scaleX, -25.0f, -64.0 * scaleZ); // Getting the terrain somewhat in the middle
	//startPos = glm::vec3(-64.0f * scaleX, -50.0f, -64.0 * scaleZ); // Getting the terrain somewhat in the middle
	//glm::vec3 startPos = glm::vec3(-64.0f , -25.0f, -64.0 );

	if (!hasTexture) {

		glBindVertexArray(VAO);
		model = glm::translate(model, startPos);
		ourShader->setMat4("model", model);

		//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 4);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


	}
	else {										// RENDERING WHEN USING TEXTURE COORDS
		glBindVertexArray(VAO);
		model = glm::translate(model, startPos);

		//ourShader->setMat4("model", model);
		sharedShader->use();
		sharedShader->setMat4("model", model);


		terrainTexture->bindTexture(0);

		//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 5);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		terrainTexture->unbind();
	}
	glBindVertexArray(0);
}

bool Terrain::setUpTerrainData(bool hasTexture)
{
	this->hasTexture = hasTexture;
	if (hasTexture == false) {
		// use shaders for no texture terrain
		ourShader = new Shader("shaders/vertexShader_terrain.shader", "shaders/fragmentShader_terrain.shader");


		// step 1) : set up new vertex array
		/*
			plan:
				-Each byte from the height map I guess represents 3 points. Use a Vector of floats? ( fill up Vector of floats with vertex data ( pos + color)
				-Use the algorithm from the lecture render() function to fill the vector instead of using it to render ( render later )


		*/

		unsigned char hcolor;  //color of the height 

	 //loop through the z axis 
		for (int z = 0; z < size ; z++) {
			//loop through the x axis 
			//glBegin(GL_TRIANGLE_STRIP);
			for (int x = 0; x < size; x++) {
				//create the the first point in the triangle strip 
				hcolor = getHeightColor(x, z);

				vertices.push_back((float)x * scaleX);
				vertices.push_back(getHeight(x, z));
				vertices.push_back((float)z * scaleZ);

				//vertices.push_back(hcolor);
				vertices.push_back((float)hcolor);

				// Only generate indices if NOT at the edge of the terrain data grid
				if (x < size - 1 && z < size - 1) 
				{
					unsigned int topLeft = z * size + x;
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
			//glEnd();
		}

		std::cout << "Number of elements = " << vertices.size() << std::endl;


		// step 2) : set up VAO and VBO

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


		//---------------------------
	}
	else { // setting up vertex to include Texture Coorindates

		// use shaders for textured terrain
		ourShader = new Shader("shaders/vertexShader.shader", "shaders/fragmentShader.shader");
		// INSTEAD USE SHARED SHADER WHEN DRAWING


		unsigned char hcolor;  //color of the height 
		float texLeft;
		float texBottom;
		float texTop;
	
		// TESTING TO SEE IF THIS DRAWS BETTER, IF NOT THEN DELETE THIS, DELETE EBO CHANGE, AND REVERT BACK TO DRAW ARRAYS
		for (int z = 0; z < size; z++) 
		{
			for (int x = 0; x < size; x++)
			{
				// Create the vertex at (x, z)
				hcolor = getHeightColor(x, z);
				vertices.push_back((float)x * scaleX);
				vertices.push_back(getHeight(x, z));
				vertices.push_back((float)z * scaleZ);

				// just storing the vertex pos separately just to test something ( delete this once done )
				vert_pos.push_back((float)x* scaleX);
				vert_pos.push_back(getHeight(x, z));
				vert_pos.push_back((float)z* scaleZ);
				//----------------------


				// Calculate normals
				float currentX = (float)x * scaleX;
				float currentY = getHeight(x, z);
				float currentZ = (float)z * scaleZ;

				// get height values of the left, right vertices along the x-axis
				// get height values of the up and down vertices along the z-axis
				// create a vector using the differences in height values along the X and Z axes
				// constant y value to ensure normals have a consistent length along the y-axis
				// normalise the resulting vector to obtain the current vertex

				float heightLeft = x > 0 ? getHeight(x - 1, z) : currentY;
				float heightRight = x < size - 1 ? getHeight(x + 1, z) : currentY;
				float heightUp = z > 0 ? getHeight(x, z - 1) : currentY;
				float heightDown = z < size - 1 ? getHeight(x, z + 1) : currentY;

				glm::vec3 normal = glm::normalize(glm::vec3(
					heightLeft - heightRight,
					2.0f,
					heightUp - heightDown
				));

				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
				//----------------------------------------


				// Add texture coordinates
				texLeft = (float)x / size;
				texBottom = (float)z / size;
				vertices.push_back(texLeft);
				vertices.push_back(texBottom);



				// Only generate indices if NOT at the edge of the terrain data grid
				if (x < size - 1 && z < size - 1) {
					unsigned int topLeft = z * size + x;
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

				// Example of the formula 
				/*
				The grid is of size size x size, so there are size number of vertices in each row.
					For each row z, there are size* z vertices that come before the current row in the vertices vector.
					Within the current row, there are x vertices that come before the topLeft vertex.
					So, to find the index of the topLeft vertex, we sum the number of vertices that came before it in previous rows(size* z)
					and the number of vertices that came before it in the current row(x).
				*/


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
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		ourShader->use(); // below we are telling OpenGL which texture unit each shader sampler belongs to 
		ourShader->setInt("texture1", 0);
	}
	return 0;
}


void Terrain::loadTerrainTexture(std::string textureName)
{
	// Terrain texture data
	TextureFactory textFact; 
	terrainTexture = textFact.createTexture(textureName); // returns unique pointer
	terrainTexture->load();

}


float Terrain::getHeight(int xpos, int zpos) {

	if (xpos < size && zpos < size && xpos >=0 && zpos >= 0) {


		return ((float)(terrainData[(zpos * size) + xpos]) * scaleY);
	}
	
}
unsigned char Terrain::getHeightColor(int xpos, int zpos) 
{
	if (xpos < size && zpos < size)
	{
		return terrainData[zpos * size + xpos];
	}
	return 1;
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

	// allocate memory for heightfield array
	size = hSize;
	heights = new float[size * size]; // allocate memory
	terrainData = new unsigned char[size * size]; // terrainData is declared in terrain class
	if (heights == NULL || terrainData == NULL) {
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

		// pick up the second random point P2(x2, z2) and make sure it is 
		// different from the first point 
		do {
			x2 = (rand() % size);
			z2 = (rand() % size);
		} while (x2 == x1 && z2 == z1);

		//for each point P(x, z) in the field, calculate the new height values 
		for (int z = 0; z < size; z++) {
			for (int x = 0; x < size; x++) {
				// determine which side of the line P1P2 the point P lies in 
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
					heights[(z * size) + x] += (float)displacement;
				}
			}
		}
		addFilter(heights, weight);
	}

	// normalise the heightfield
	normaliseTerrain(heights);

	// copy the float heightfield to terrainData (in unsign char) 
	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			//setHeightAtPoint((unsigned char)heights[(z * size) + x], x, z);
			terrainData[(z * size) + x] = heights[(z * size) + x]; // DOUBLE CHECK THIS PLEASE FOR THE LOVE OF GOD
		}
	}

	// dispose of the temporary array heights 
	delete[] heights;
	return true;

}

void Terrain::addFilter(float* terData, float weight)
{

	int i;

	//erode left to right, starting from the beginning of each row 
	for (i = 0; i < size; i++)
		filterPass(&terData[size * i], 1, weight);

	//erode right to left, starting from the end of each row 
	for (i = 0; i < size; i++)
		filterPass(&terData[size * i + size - 1], -1, weight);

	//erode top to bottom, starting from the beginning of each column 
	for (i = 0; i < size; i++)
		filterPass(&terData[i], size, weight);

	//erode from bottom to top, starting from the end of each column 
	for (i = 0; i < size; i++)
		filterPass(&terData[size * (size - 1) + i], -size, weight);

}

void Terrain::filterPass(float* startP, int increment, float weight)
{
	float yprev = *startP;   // the starting point in the terrain array 
	int j = increment;   // must be either +1, -1, +size, or -size 
	float k = weight;

	// loop through either  
	 //      one row from left to right if increment = +1, or 
	 //      one row from right to left if increment = -1, or 
	 //      one column from top to bottom if increment = +size, or 
	 //      one column from bottom to top if increment = -size 

	for (int i = 1; i < size; i++) {
		// yi = k yi-1 + (1-k) xi 
		*(startP + j) = k * yprev + (1 - k) * (*(startP + j));
		yprev = *(startP + j);
		j += increment;
	}
}


void Terrain::normaliseTerrain(float* terData)
{
	float fMin = terData[0];
	float fMax = terData[0];
	float fHeight;
	int i;

	// find the min and max values of the height terrainData
	for (i = 1; i < size * size; i++) {
		if (terData[i] > fMax)
			fMax = terData[i];
		else if (terData[i] < fMin)
			fMin = terData[i];
	}
	//find the range of the altitude 
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255
	for (i = 0; i < size * size; i++)
	{
		terData[i] = ((terData[i] - fMin) / fHeight) * 255.0f;
	}
}
