#ifndef ASTEROID_H
#define ASTEROID_H

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"
#include <vector>

class Asteroid : public MovingObject {
public:
    // Constructor
    Asteroid(const threepp::Vector3& position, float mass, const threepp::Color& color);

    // Update method for derived class
    void update(float deltaTime) override;

    // Spawn asteroid at screen edges
    // Had some problems refactoring asked GPT for help
    static std::shared_ptr<Asteroid> spawnAsteroid(
        float left, float right, float top, float bottom, threepp::Scene& scene);

    // Return radius for collision detection
    float getRadius() const override;

    // Getter for velocity
    const threepp::Vector3& getVelocity() const;

    // Setter for velocity
    void setVelocity(const threepp::Vector3& velocity);

    // Getter for mass
    float getMass() const;

    // Static method to initialize spawn timers
    static void initializeSpawnTimers();

    // Update and manage all asteroids
    static void updateAsteroids(
        float deltaTime,
        float left,
        float right,
        float top,
        float bottom,
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        threepp::Scene& scene,
        float timeAlive);

private:
    // Static variables for spawn timing
    static float timeSinceLastSpawn;
    static float spawnInterval;
};

#endif // ASTEROID_H
