#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LabPhysics {
	/**
	 * @brief Represents an Axis-Aligned Bounding Box (AABB) in 3D space.
	 */
	class AABB
	{
	private:
		// Private members

	public:
		// Public members
		glm::vec3 boxSize; ///< The size of the AABB along each axis.
		glm::vec3 min;     ///< The minimum corner of the AABB.
		glm::vec3 max;     ///< The maximum corner of the AABB.

		/**
		 * @brief Constructs an AABB with a specified box size.
		 *
		 * @param boxSize The size of the AABB along each axis. Default is (1.0f, 1.0f, 1.0f).
		 */
		AABB(const glm::vec3& boxSize = glm::vec3(1.0f, 1.0f, 1.0f))
			: boxSize(boxSize), min(-boxSize * 0.5f), max(boxSize * 0.5f) {}

		/**
		 * @brief Updates the position of the AABB.
		 *
		 * @param position The new position of the AABB.
		 */
		void updateAABBPosition(glm::vec3 position)
		{
			min = position - boxSize * 0.5f;
			max = position + boxSize * 0.5f;
		}

		// Additional functions to access min, max, and boxSize if needed
		/*const glm::vec3& getMin() const { return min; }
		const glm::vec3& getMax() const { return max; }
		const glm::vec3& getBoxSize() const { return boxSize; }*/
	};
}
