#ifndef BULLET_H
#define BULLET_H

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet : public MovingObject {
public:
    // Constructor to initialize the bullet
    Bullet(const Vector3& position, float angle, float speed, const Color& color);

    // Update the bullet's position
    void update(float deltaTime) override;

    // Check if the bullet is active (still within its lifespan)
    bool isActiveBullet() const;

    // Return "radius" of Bullet for collision detection
    float getRadius() const override;

private:
    float lifespan;
    bool isActive = true;
};

#endif // BULLET_H
