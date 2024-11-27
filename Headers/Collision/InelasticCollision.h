#ifndef INELASTICCOLLISION_HPP
#define INELASTICCOLLISION_HPP

#include "Sprites/Asteroid.h"
#include "Sprites/Bullet.h"
#include "threepp/threepp.hpp"
#include <vector>
#include <memory>

using namespace threepp;

class InelasticCollision {
public:
    static void handleCollisions(
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        std::vector<std::shared_ptr<Bullet>>& bullets,
        std::shared_ptr<Scene>& scene,
        int& score,          // Reference to score
        float timeAlive,     // Time alive
        float scoreMult      // Score multiplier
    );
};

#endif // INELASTICCOLLISION_HPP
