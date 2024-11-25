#ifndef INELASTICCOLLISION_HPP
#define INELASTICCOLLISION_HPP

#include "threepp/threepp.hpp"
#include "Collision/BaseCollisionDetector.h"
#include "Sprites/Asteroid.h"
#include "Sprites/Bullet.h"
#include <vector>
#include <memory>

using namespace threepp;

class InelasticCollision {
public:
    static void handleCollisions(
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        std::vector<std::shared_ptr<Bullet>>& bullets,
        std::shared_ptr<Scene>& scene);
};

#endif // INELASTICCOLLISION_HPP
