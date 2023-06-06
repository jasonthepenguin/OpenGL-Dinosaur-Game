

#include "entityManager.h"




NPC* entityManager::getEntityFromID(int id) const {
	//find the entity
	std::map<int, NPC*>::const_iterator ent = entityMap.find(id);
	if (ent == entityMap.end())
		return NULL;
	return ent->second;
}
void entityManager::removeEntity(NPC* pEntity) {
	entityMap.erase(entityMap.find(pEntity->getID()));
}
void entityManager::registerEntity(NPC* newEntity) {
	entityMap.insert(std::make_pair(newEntity->getID(), newEntity));
}