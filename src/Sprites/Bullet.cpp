#include "Sprites/Bullet.h"
#include <cmath> // Include for std::sin and std::cos

Bullet::Bullet(const Vector3& position, float angle, float speed, const Color& color)
    : MovingObject(position, 0.1f), lifespan(2.0f) {

    auto geometry = CylinderGeometry::create(0.05f, 0.05f, 0.1f);
    auto material = MeshBasicMaterial::create({{"color", color}});

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_);

    // Calculate initial velocity based on angle and speed
    velocity_ = Vector3(-std::sin(angle), std::cos(angle), 0) * speed;
}

void Bullet::update(float deltaTime) {
    applyPhysics(deltaTime);

    // Decrease the lifespan
    lifespan -= deltaTime;

    // Set inactive if the lifespan is over
    if (lifespan <= 0.0f) {
        isActive = false;
    }
}

bool Bullet::isActiveBullet() const {
    return isActive;
}

float Bullet::getRadius() const {
    return 0.1f;
}
