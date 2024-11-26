#include "Collision/BaseCollisionDetector.h"

bool BaseCollisionDetector::hasCollided(const std::shared_ptr<MovingObject>& obj1, const std::shared_ptr<MovingObject>& obj2) {
    return hasCollided(*obj1, *obj2);
}

bool BaseCollisionDetector::hasCollided(const std::shared_ptr<MovingObject>& obj1, const MovingObject& obj2) {
    return hasCollided(*obj1, obj2);
}

bool BaseCollisionDetector::hasCollided(const MovingObject& obj1, const MovingObject& obj2) {
    const auto& pos1 = obj1.getPosition();
    const auto& pos2 = obj2.getPosition();

    // Distance between objects
    float distance = pos1.distanceTo(pos2);

    // Check if the distance is less than the sum of their radii
    float combinedRadius = obj1.getRadius() + obj2.getRadius();
    return distance <= combinedRadius;
}
