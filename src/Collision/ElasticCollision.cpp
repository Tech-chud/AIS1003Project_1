#include "Collision/ElasticCollision.h"
#include "threepp/threepp.hpp"
#include <cmath>
#include <iostream>


void ElasticCollision::handleCollisions(std::vector<std::shared_ptr<Asteroid>>& asteroids) {
    // Got some help here from GPT for checking two objects inside vector
    // And some general help when faultfinding why elastic colisons wouldnt work, math is allmost all gpt...
    for (size_t i = 0; i < asteroids.size(); ++i) {
        for (size_t j = i + 1; j < asteroids.size(); ++j) {
            auto& asteroid1 = asteroids[i];
            auto& asteroid2 = asteroids[j];

            // Check if the two asteroids collide
            if (BaseCollisionDetector::hasCollided(asteroid1, asteroid2)) {

                Vector3 pos1 = asteroid1->getPosition();
                Vector3 pos2 = asteroid2->getPosition();


                Vector3 vel1 = asteroid1->getVelocity();
                Vector3 vel2 = asteroid2->getVelocity();

                // Masses currently not used however maybe when splitting asteroids one smaller will have less mass = different collision
                float mass1 = asteroid1->getMass();
                float mass2 = asteroid2->getMass();

                // Compute the normal vector
                Vector3 collisionNormal = (pos2 - pos1).normalize();

                // Compute the relative velocity
                Vector3 relativeVelocity = vel2 - vel1;

                // Compute the velocity along the normal
                float velocityAlongNormal = relativeVelocity.dot(collisionNormal);

                // Skip if the objects are separating
                if (velocityAlongNormal > 0) {
                    continue;
                }

                // Elastic collision response
                float restitution = 1.0f; // Perfectly elastic collision
                float impulse = -(1 + restitution) * velocityAlongNormal /
                                (1 / mass1 + 1 / mass2);

                Vector3 impulseVector = collisionNormal * impulse;

                // Update velocities
                asteroid1->setVelocity(vel1 - impulseVector / mass1);
                asteroid2->setVelocity(vel2 + impulseVector / mass2);
            }
        }
    }

}

void ElasticCollision::handleAsteroidPlayerCollision(
    std::vector<std::shared_ptr<Asteroid>>& asteroids,
    Player& player,
    std::shared_ptr<threepp::Scene>& scene,
    float deltaTime) {

    static float collisionCooldown = 0.0f;
    static std::shared_ptr<Asteroid> collidingAsteroid = nullptr;

    if (collisionCooldown > 0.0f) {
        collisionCooldown -= deltaTime;

        // Visual indicator: Player is in cooldown
        player.setColor(threepp::Color::red);

        // Check if the player is still colliding with the same asteroid
        if (collidingAsteroid && BaseCollisionDetector::hasCollided(collidingAsteroid, player)) {
            // If still colliding, reset cooldown
            collisionCooldown = 1.0f;
            return;
        } else {
            // If no longer colliding, reset the collidingAsteroid pointer
            collidingAsteroid = nullptr;
        }
    } else {
        // Visual indicator: Player is out of cooldown
        player.setColor(threepp::Color::white);
    }

    for (auto& asteroid : asteroids) {
        // Check for collision between the player and the asteroid
        if (BaseCollisionDetector::hasCollided(asteroid, player) && collisionCooldown <= 0.0f) {
            std::cout << "Asteroid-Player collision detected!" << std::endl;

            // Get positions and velocities
            threepp::Vector3 asteroidVelocity = asteroid->getVelocity();
            threepp::Vector3 playerVelocity = player.getVelocity();
            threepp::Vector3 asteroidPosition = asteroid->getPosition();
            threepp::Vector3 playerPosition = player.getPosition();

            // Compute collision normal
            threepp::Vector3 collisionNormal = (asteroidPosition - playerPosition).normalize();

            // Compute relative velocity
            threepp::Vector3 relativeVelocity = asteroidVelocity - playerVelocity;

            // Compute velocity along collision normal
            float velocityAlongNormal = relativeVelocity.dot(collisionNormal);

            // Skip if the objects are separating
            if (velocityAlongNormal > 0) {
                continue;
            }

            // Masses
            float asteroidMass = asteroid->getMass();
            float playerMass = player.getMass();

            // Compute impulse scalar
            float restitution = 1.0f; // Perfectly elastic collision
            float impulse = -(1 + restitution) * velocityAlongNormal / (1 / asteroidMass + 1 / playerMass);

            // Compute impulse vector
            threepp::Vector3 impulseVector = collisionNormal * impulse;

            // Update asteroid velocity
            asteroidVelocity += impulseVector / asteroidMass;
            asteroid->setVelocity(asteroidVelocity);

            // Set cooldown and track colliding asteroid
            collisionCooldown = 1.0f; // Cooldown in seconds
            collidingAsteroid = asteroid;

            // Break out of loop to prevent multiple collisions in the same frame
            break;
        }
    }
}
