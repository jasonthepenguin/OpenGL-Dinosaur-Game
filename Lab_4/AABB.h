#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LabPhysics {
	class AABB
	{

	private:




	public:

		glm::vec3 boxSize;


		glm::vec3 min;
		glm::vec3 max;


		// Constructor
		AABB(const glm::vec3& boxSize = glm::vec3(1.0f, 1.0f, 1.0f))
			: boxSize(boxSize), min(-boxSize * 0.5f), max(boxSize * 0.5f) {}

		void updateAABBPosition(glm::vec3 position)
		{
			min = position - boxSize * 0.5f;
			max = position + boxSize * 0.5f;
		}

		// Additional functions to access min, max and boxSize if needed
		/*const glm::vec3& getMin() const { return min; }
		const glm::vec3& getMax() const { return max; }
		const glm::vec3& getBoxSize() const { return boxSize; }*/


	};

}