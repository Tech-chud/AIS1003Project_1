#ifndef ELASTICCOLLISION_HPP
#define ELASTICCOLLISION_HPP

#include "Sprites/Asteroid.h"
#include "Collision/BaseCollisionDetector.h"
#include "Sprites/Player.h"
#include <vector>
#include <memory>

class ElasticCollision {
public:

    static void handleAsteroidCollisions(std::vector<std::shared_ptr<Asteroid>>& asteroids);

    static void handleAsteroidPlayerCollision(
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        Player& player,
        std::shared_ptr<threepp::Scene>& scene,
        float deltaTime,
        int& health,      // Reference to modify health
        float damageMult  // Multiplier for velocity-based damage
    );
};

#endif // ELASTICCOLLISION_HPP
