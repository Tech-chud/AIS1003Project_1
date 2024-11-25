#include "Collision/InelasticCollision.h"

void InelasticCollision::handleCollisions(
    std::vector<std::shared_ptr<Asteroid>>& asteroids,
    std::vector<std::shared_ptr<Bullet>>& bullets,
    std::shared_ptr<Scene>& scene) {

    //Code for Bullet Asteroid Collision
    //Gpt was used for help for some of this
    for (auto itA = asteroids.begin(); itA != asteroids.end();) {
        bool asteroidRemoved = false;

        for (auto itB = bullets.begin(); itB != bullets.end();) {
            if (BaseCollisionDetector::hasCollided(*itA, *itB)) {
                // Handle collision by removing from the scene
                scene->remove(*(*itA)->getMesh());
                scene->remove(*(*itB)->getMesh());

                // Erase bullet from vector and break the inner loop
                itB = bullets.erase(itB);
                asteroidRemoved = true;
            } else {
                ++itB;
            }
        }

        // If the asteroid was hit, remove it from the vector
        if (asteroidRemoved) {
            itA = asteroids.erase(itA);
        } else {
            ++itA;
        }
    }
}