
#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"
#include <memory>

using namespace threepp;

class Asteroid : public MovingObject {
public:
    // Constructor for Asteroid
    Asteroid(const Vector3& position, float mass, const Color& color);

    // Implement the update method (overrides the pure virtual method in MovingObject)
    void update(float deltaTime) override;

    // Static function to spawn asteroids at the edges of the screen
    static std::shared_ptr<Asteroid> spawnAsteroid(float left, float right, float top, float bottom, Scene& scene);

    // Return "radius" of Asteroid for collision detection
    float getRadius() const override;
};

#endif // ASTEROID_HPP

