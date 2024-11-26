#ifndef BASECOLLISIONDETECTOR_H
#define BASECOLLISIONDETECTOR_H

#include "Util/MovingObjects.h"
#include <memory>

class BaseCollisionDetector {
public:
    // Check if two shared_ptr objects collide
    static bool hasCollided(const std::shared_ptr<MovingObject>& obj1, const std::shared_ptr<MovingObject>& obj2);

    // Check if a shared_ptr object and a raw object collide
    static bool hasCollided(const std::shared_ptr<MovingObject>& obj1, const MovingObject& obj2);

    // Check if two raw objects collide
    static bool hasCollided(const MovingObject& obj1, const MovingObject& obj2);
};

#endif // BASECOLLISIONDETECTOR_H
