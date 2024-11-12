//
// Created by borga on 12/11/2024.
//

#ifndef BASECOLLISIONDETECTOR_HPP
#define BASECOLLISIONDETECTOR_HPP

#include "../Util/MovingObjects.h"
#include <memory>

class BaseCollisionDetector {
public:
    // Method to check if two MovingObject instances have collided
    static bool hasCollided(const std::shared_ptr<MovingObject>& obj1, const std::shared_ptr<MovingObject>& obj2) {
        // Get the positions of both objects
        const auto& pos1 = obj1->getPosition();
        const auto& pos2 = obj2->getPosition();

        // Calculate the distance between the two objects
        float distance = pos1.distanceTo(pos2);

        // Check if the distance is less than the sum of their radii (simple circular collision detection)
        float combinedRadius = obj1->getRadius() + obj2->getRadius(); // Ensure getRadius() is defined in MovingObject
        return distance <= combinedRadius;
    }
};

#endif // BASECOLLISIONDETECTOR_HPP

