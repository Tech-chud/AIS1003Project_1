#ifndef BASECOLLISIONDETECTOR_HPP
#define BASECOLLISIONDETECTOR_HPP

#include "Util/MovingObjects.h"
#include <memory>

class BaseCollisionDetector {
public:
    // Check if two objects collide
    static bool hasCollided(const std::shared_ptr<MovingObject>& obj1, const std::shared_ptr<MovingObject>& obj2);
};

#endif // BASECOLLISIONDETECTOR_HPP
