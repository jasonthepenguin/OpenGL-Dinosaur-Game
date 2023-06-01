#pragma once

#include "GameObject.h"

#include <vector>


class PhysicsController
{

public:
    bool checkCollision(GameObject* gameObject1, GameObject* gameObject2)
    {
        auto box1 = gameObject1->getAABB();
        auto box2 = gameObject2->getAABB();

        if (box1 != nullptr && box2 != nullptr) {
            if (AABBcollisionCheck(box1, box2))
            {
                gameObject2->collisionEvent(gameObject1);
                gameObject1->collisionEvent(gameObject2);
                return true;
            }
           

        }

        return false;
    }

    bool AABBcollisionCheck(const LabPhysics::AABB* box1, const LabPhysics::AABB* box2)
    {
        return (box1->min.x <= box2->max.x && box1->max.x >= box2->min.x) &&
            (box1->min.y <= box2->max.y && box1->max.y >= box2->min.y) &&
            (box1->min.z <= box2->max.z && box1->max.z >= box2->min.z);
    }

    void update(std::vector<GameObject*>& gameObjects)
    {
        for (size_t i = 0; i < gameObjects.size(); ++i)
        {
            for (size_t j = i + 1; j < gameObjects.size(); ++j)
            {
                checkCollision(gameObjects[i], gameObjects[j]);
            }
        }

    }


};