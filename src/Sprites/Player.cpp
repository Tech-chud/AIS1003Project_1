#include "Sprites/Player.h"
#include <cmath> // Include for std::sin and std::cos

Player::Player(const Vector3& position, float mass, const Color& color)
    : MovingObject(position, mass), rotationAngle(0.0f), thrustPower(15.0f), maxSpeed(8.0f), rotationSpeed(2.0f) {

    auto geometry = ConeGeometry::create(0.2, 0.5, 3); // Triangle shape for spaceship
    auto material = MeshBasicMaterial::create({{"color", color}});

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_);

    material_ = material;
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
    return 0.15f;
}

Vector3 Player::getVelocity() const {
    return velocity_;
}

void Player::setVelocity(const Vector3& velocity) {
    velocity_ = velocity;
}

float Player::getMass() const {
    return mass_;
}

void Player::setMass(float mass) {
    mass_ = mass;
}

void Player::setPosition(const Vector3& position) {
    position_ = position;
    mesh_->position.copy(position);
}

void Player::setColor(const Color& color) {
    material_->color = color;
}