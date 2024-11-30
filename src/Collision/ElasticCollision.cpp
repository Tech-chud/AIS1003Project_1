#include "Collision/ElasticCollision.h"
#include "threepp/threepp.hpp"
#include <cmath>
#include <iostream>
#include <unordered_set> //Had problems with multi-colision on same asteroid asked chatgpt and they used this as a dependancy dont know if ill keep this


void ElasticCollision::handleAsteroidCollisions(std::vector<std::shared_ptr<Asteroid>>& asteroids) {
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

                // Masses currently not used however may be used in the future when splitting asteroids one smaller will have less mass = different collision
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
    // GPT Was used here for general math questions and some help
    // and for faultfinding a problem with a reoccurring problem with an asteroid giving multiple collisions to player even in cooldown
std::vector<std::shared_ptr<Asteroid>>& asteroids,
    Player& player,
    std::shared_ptr<threepp::Scene>& scene,
    float deltaTime,
    int& health,
    float damageMult) {

    static float collisionCooldown = 0.0f;
    static std::unordered_set<std::shared_ptr<Asteroid>> collidingAsteroids;

    // Cooldown logic
    if (collisionCooldown > 0.0f) {
        collisionCooldown -= deltaTime;

        player.setColor(threepp::Color::red);

        // Remove asteroids that are no longer colliding
        for (auto it = collidingAsteroids.begin(); it != collidingAsteroids.end();) {
            if (!BaseCollisionDetector::hasCollided(*it, player)) {
                it = collidingAsteroids.erase(it);
            } else {
                ++it;
            }
        }

        return; // Skip further collision handling during cooldown
    } else {
        player.setColor(threepp::Color::white);
    }

    for (auto& asteroid : asteroids) {
        // If already colliding with this asteroid, skip
        if (collidingAsteroids.find(asteroid) != collidingAsteroids.end()) {
            continue;
        }

        // Check for collision between the player and the asteroid
        if (BaseCollisionDetector::hasCollided(asteroid, player) && collisionCooldown <= 0.0f) {
            std::cout << "Asteroid-Player collision detected!" << std::endl;

            // Add the asteroid to the colliding set
            collidingAsteroids.insert(asteroid);

            // Get positions and velocities
            threepp::Vector3 asteroidVelocity = asteroid->getVelocity();
            threepp::Vector3 playerVelocity = player.getVelocity();

            // Compute collision normal
            threepp::Vector3 collisionNormal = (asteroid->getPosition() - player.getPosition()).normalize();

            // Compute relative velocity along the collision normal
            threepp::Vector3 relativeVelocity = asteroidVelocity - playerVelocity;
            float velocityAlongNormal = relativeVelocity.dot(collisionNormal);

            // Skip if the objects are separating
            if (velocityAlongNormal > 0) {
                continue;
            }

            // Masses (Currently not used maybe later if i decide to make splitting asteroids)
            float asteroidMass = asteroid->getMass();
            float playerMass = player.getMass();

            // Compute impulse scalar
            float restitution = 1.0f; // Perfectly elastic collision
            float impulse = -(1 + restitution) * velocityAlongNormal / (1 / asteroidMass + 1 / playerMass);

            // Compute impulse vector
            threepp::Vector3 impulseVector = collisionNormal * impulse;

            // Update asteroid velocity based on player's velocity
            asteroidVelocity += impulseVector / asteroidMass;
            asteroid->setVelocity(asteroidVelocity);

            // Slight backwards nudge on player on collision
            threepp::Vector3 nudgeVector = collisionNormal * -0.5f;
            player.setVelocity(nudgeVector);

            // Calculate velocity-based damage
            float collisionVelocity = relativeVelocity.length();
            int damage = static_cast<int>(20 + collisionVelocity * damageMult);
            health = std::max(0, health - damage); // Ensure health doesn't drop below 0

            std::cout << "Player hit! Damage: " << damage << ", Health: " << health << std::endl;

            // Set collision cooldown "invis frames"
            collisionCooldown = 1.0f; // Cooldown in seconds

            break; // Only process one collision per frame
        }
    }
}