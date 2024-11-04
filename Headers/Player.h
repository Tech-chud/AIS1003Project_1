#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "MovingObjects.h"
#include "threepp/threepp.hpp"

using namespace threepp;

class Player : public MovingObject {
public:
    // Constructor with initial position and color
    Player(const Vector3& position, float mass, const Color& color)
        : MovingObject(position, mass), rotationAngle(0.0f), thrustPower(5.0f), maxSpeed(10.0f) {

        // Define player-specific geometry and material
        auto geometry = ConeGeometry::create(0.2, 0.5, 3);
        auto material = MeshBasicMaterial::create({{"color", color}});

        // Create the mesh for the player
        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position_);
    }

    // Rotate the player based on input
    void rotate(float angleDelta) {
        rotationAngle += angleDelta;
        mesh_->rotation.z = -rotationAngle; // Rotate around the z-axis
    }

    // Apply thrust in the forward direction
    void applyThrust() {
        // Convert rotation angle to radians
        float angleRad = rotationAngle;

        // Calculate thrust direction based on rotation
        Vector3 thrustDirection(std::cos(angleRad), std::sin(angleRad), 0);

        // Apply thrust to the velocity
        velocity_ += thrustDirection * thrustPower * 0.1f;

        // Limit the speed to a maximum value
        if (velocity_.length() > maxSpeed) {
            velocity_.normalize();
            velocity_ *= maxSpeed;
        }
    }

    // Update the player's position
    void update(float deltaTime) override {
        // Simulate drift by applying current velocity to position
        applyPhysics(deltaTime);

        // Slowly decay the velocity to create a floaty effect
        velocity_ *= 0.99f; // Apply a small damping factor for a more controlled drift
    }

private:
    float rotationAngle;    // The current rotation angle of the spaceship
    float thrustPower;      // The force applied when thrusting
    float maxSpeed;         // Maximum speed limit for the spaceship
};

#endif // PLAYER_HPP
