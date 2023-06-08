#pragma once

#include "NPC.h"
#include <map>
#include <string>

/**
 * @brief The entityManager class manages a collection of entities.
 */
class entityManager
{
private:
	/**
	 * @brief A map that stores entities by their identifying number.
	 */
	std::map<int, NPC*> entityMap;

public:
	/**
	 * @brief Registers a new entity in the entityManager.
	 *
	 * @param NewEntity A pointer to the entity to be registered.
	 */
	void registerEntity(NPC* NewEntity);

	/**
	 * @brief Retrieves an entity from the entityManager based on its ID.
	 *
	 * @param id The ID of the entity to retrieve.
	 * @return NPC* A pointer to the retrieved entity. Returns nullptr if no entity is found.
	 */
	NPC* getEntityFromID(int id) const;

	/**
	 * @brief Removes an entity from the entityManager.
	 *
	 * @param pEntity A pointer to the entity to be removed.
	 */
	void removeEntity(NPC* pEntity);

	/**
	 * @brief Applies a function to each entity in the entityManager.
	 *
	 * @tparam Func The type of the function to apply to each entity.
	 * @param func The function to apply to each entity.
	 */
	template <typename Func>
	void forEachEntity(Func&& func) const {
		for (const auto& entityPair : entityMap) {
			func(entityPair.second);
		}
	}
};
