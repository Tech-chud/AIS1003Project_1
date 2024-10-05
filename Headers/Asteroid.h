#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "MovingObjects.h"

class Asteroid : public MovingObject {
public:
    // Constructor for Asteroid
    Asteroid(const Vector3& position, float mass, const Color& color)
        : MovingObject(position, mass, color) {
        // Custom geometry or other asteroid-specific attributes if needed
    }

    // Implement the update method
    void update(float deltaTime) override {
        // Example: rotate the asteroid over time (just for visual interest)
        mesh_->rotation.z += 0.5f * deltaTime;

        // Apply physics for movement
        applyPhysics(deltaTime);
    }
};

#endif // ASTEROID_HPP
