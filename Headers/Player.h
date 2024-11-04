#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "MovingObjects.h"
#include "threepp/threepp.hpp"

using namespace threepp;

class Player : public MovingObject {
public:
    // Constructor with initial position and color
    Player(const Vector3& position, float mass, const Color& color)
        : MovingObject(position, mass), rotationAngle(0.0f), thrustPower(20.0f), maxSpeed(10.0f), rotationSpeed(2.0f) {

        // Define player-specific geometry and material
        auto geometry = ConeGeometry::create(0.2, 0.5, 3); // Triangle shape for spaceship
        auto material = MeshBasicMaterial::create({{"color", color}});

        // Create the mesh for the player
        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position_);
    }

    // Rotate the player based on input, with dt
    void rotate(float direction, float deltaTime) {
        rotationAngle += direction * rotationSpeed * deltaTime;
        mesh_->rotation.z = +rotationAngle;
    }

    // Apply thrust in the forward direction, with deltaTime for consistent acceleration
    void applyThrust(float deltaTime) {
        float angleRad = rotationAngle;
        Vector3 thrustDirection(std::cos(angleRad), std::sin(angleRad), 0);

        // Apply thrust proportional to deltaTime
        velocity_ += thrustDirection * thrustPower * deltaTime;

        // Limit the speed to a maximum value
        if (velocity_.length() > maxSpeed) {
            velocity_.normalize();
            velocity_ *= maxSpeed;
        }
    }

    // Update the player's position
    void update(float deltaTime) override {
        // Apply physics (velocity-based position update)
        applyPhysics(deltaTime);

        // Floaty
        velocity_ *= std::pow(0.99f, deltaTime * 60.0f);
    }

private:
    float rotationAngle;
    float thrustPower;
    float maxSpeed;
    float rotationSpeed;
};

#endif // PLAYER_HPP
