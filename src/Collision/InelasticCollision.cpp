#include "Collision/InelasticCollision.h"
#include "Collision/BaseCollisionDetector.h"
#include <iostream>

void InelasticCollision::handleCollisions(
    std::vector<std::shared_ptr<Asteroid>>& asteroids,
    std::vector<std::shared_ptr<Bullet>>& bullets,
    std::shared_ptr<Scene>& scene,
    int& score,
    float timeAlive,
    float scoreMult) {

    for (auto itA = asteroids.begin(); itA != asteroids.end();) {
        bool asteroidRemoved = false;

        for (auto itB = bullets.begin(); itB != bullets.end();) {
            if (BaseCollisionDetector::hasCollided(*itA, *itB)) {
                // Handle collision by removing from the scene
                scene->remove(*(*itA)->getMesh());
                scene->remove(*(*itB)->getMesh());

                // Calculate score increment: 1 + timeAlive * scoreMult
                int pointsEarned = static_cast<int>(1 + timeAlive * scoreMult);
                score += pointsEarned;

                // Log points for debugging
                std::cout << "Asteroid destroyed! +" << pointsEarned
                          << " points. Total Score: " << score << std::endl;

                // Remove bullet
                itB = bullets.erase(itB);
                asteroidRemoved = true;
            } else {
                ++itB;
            }
        }

        // If the asteroid was hit, remove it
        if (asteroidRemoved) {
            itA = asteroids.erase(itA);
        } else {
            ++itA;
        }
    }
}
