#ifndef BULLET_HPP
#define BULLET_HPP

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

class Bullet : public MovingObject {
public:
    // Constructor
    Bullet(const Vector3& position, float angle, float speed, const Color& color);

    // Update bullet
    void update(float deltaTime) override;

    // Check if the bullet is active
    bool isActiveBullet() const;

    // Get the radius for collision detection
    float getRadius() const override;

    //function to update all bullets
    // Some functions here helped via GPT
    static void updateBullets(
        float deltaTime,
        std::vector<std::shared_ptr<Bullet>>& bullets,
        std::shared_ptr<Scene>& scene);

private:
    float lifespan;
    bool isActive;
};

#endif // BULLET_HPP
