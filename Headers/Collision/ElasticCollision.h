

#ifndef ELASTICCOLLISION_H
#define ELASTICCOLLISION_H

#ifndef ELASTICCOLLISION_HPP
#define ELASTICCOLLISION_HPP

#include "Sprites/Asteroid.h"
#include "Collision/BaseCollisionDetector.h"
#include <vector>
#include <memory>

class ElasticCollision {
public:
    // Handle elastic collisions between asteroids
    static void handleCollisions(std::vector<std::shared_ptr<Asteroid>>& asteroids);
};

#endif // ELASTICCOLLISION_HPP


#endif //ELASTICCOLLISION_H
