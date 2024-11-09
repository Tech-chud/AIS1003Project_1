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


        auto geometry = ConeGeometry::create(0.2, 0.5, 3); // Triangle shape for spaceship
        auto material = MeshBasicMaterial::create({{"color", color}});


        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position_);
    }

    // Rotate the player based on input, with dt
    void rotate(float direction, float deltaTime) {
        rotationAngle += direction * rotationSpeed * deltaTime;
        mesh_->rotation.z = +rotationAngle;
    }

    // Apply thrust in the forward direction, adjusted for upward initial orientation
    // I asked chat CPT for help on this
    void applyThrust(float deltaTime) {
        float angleRad = rotationAngle;

        // Initial direction of player
        Vector3 thrustDirection(-std::sin(angleRad), std::cos(angleRad), 0);


        velocity_ += thrustDirection * thrustPower * deltaTime;


        if (velocity_.length() > maxSpeed) {
            velocity_.normalize();
            velocity_ *= maxSpeed;
        }
    }

    // Update the player pos
    void update(float deltaTime) override {

        applyPhysics(deltaTime);


        velocity_ *= std::pow(0.99f, deltaTime * 60.0f);
    }

private:
    float rotationAngle;
    float thrustPower;
    float maxSpeed;
    float rotationSpeed;
};

#endif // PLAYER_HPP
