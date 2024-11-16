#include "Sprites/Player.h"
#include <cmath> // Include for std::sin and std::cos

Player::Player(const Vector3& position, float mass, const Color& color)
    : MovingObject(position, mass), rotationAngle(0.0f), thrustPower(20.0f), maxSpeed(10.0f), rotationSpeed(2.0f) {

    auto geometry = ConeGeometry::create(0.2, 0.5, 3); // Triangle shape for spaceship
    auto material = MeshBasicMaterial::create({{"color", color}});

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_);
}

void Player::rotate(float direction, float deltaTime) {
    rotationAngle += direction * rotationSpeed * deltaTime;
    mesh_->rotation.z = +rotationAngle;
}

void Player::applyThrust(float deltaTime) {
    float angleRad = rotationAngle;

    // Initial direction of player
    Vector3 thrustDirection(-std::sin(angleRad), std::cos(angleRad), 0);

    velocity_ += thrustDirection * thrustPower * deltaTime;

    if (velocity_.length() > maxSpeed) {
        velocity_.normalize();
        velocity_ *= maxSpeed;
    }
}

void Player::update(float deltaTime) {
    applyPhysics(deltaTime);

    // Floaty effect for slowing down
    velocity_ *= std::pow(0.99f, deltaTime * 60.0f);
}

float Player::getRotationAngle() const {
    return rotationAngle;
}

float Player::getRadius() const {
    return 0.5f;
}
