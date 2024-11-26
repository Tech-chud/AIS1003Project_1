

#ifndef ELASTICCOLLISION_H
#define ELASTICCOLLISION_H

#ifndef ELASTICCOLLISION_HPP
#define ELASTICCOLLISION_HPP

#include "Sprites/Asteroid.h"
#include "Collision/BaseCollisionDetector.h"
#include "Sprites/Player.h"
#include <vector>
#include <memory>

class ElasticCollision {
public:

    static void handleCollisions(std::vector<std::shared_ptr<Asteroid>>& asteroids);

    static void handleAsteroidPlayerCollision(
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        Player& player,
        std::shared_ptr<threepp::Scene>& scene,
        float deltaTime);
};

#endif // ELASTICCOLLISION_HPP


#endif //ELASTICCOLLISION_H
