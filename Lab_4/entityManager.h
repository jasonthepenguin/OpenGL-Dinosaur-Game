#pragma once

#include "NPC.h"
#include <map>
#include <string>


// entityManager class from topic 10 lecture notes

class entityManager
{

private:

	// to facilitate quick lookup, the entities are stored in a std::map, in which
	// pointers to entities are cross referenced by their identifying number
	std::map<int, NPC*> entityMap;

public:

	// this method stores a pointer to the entity in the Map at the index position 
// indicated by the entity's ID (makes for faster access)
	void registerEntity(NPC* NewEntity);

	NPC* getEntityFromID(int id) const;

	void removeEntity(NPC* pEntity);

	template <typename Func>
	void forEachEntity(Func&& func) const {
		for (const auto& entityPair : entityMap) {
			func(entityPair.second);
		}
	}
};

