#include "Sprites/Bullet.h"
#include <cmath> // Include for std::sin and std::cos
#include <iostream>

Bullet::Bullet(const Vector3& position, float angle, float speed, const Color& color)
    : MovingObject(position, 0.1f), lifespan(2.0f), isActive(true){

    auto geometry = CylinderGeometry::create(0.05f, 0.05f, 0.1f);
    auto material = MeshBasicMaterial::create({{"color", color}});

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_);

    // Calculate initial velocity based on angle and speed
    // Some faultfinding help from GPT
    velocity_ = Vector3(-std::sin(angle), std::cos(angle), 0) * speed;
}

//When refactoring i had some problems, GPT helped with this (commented faultfinding code)
void Bullet::update(float deltaTime) {
    applyPhysics(deltaTime);


    lifespan -= deltaTime;

    // Debug before checking the condition
    // std::cout << "Before lifespan check: Lifespan = " << lifespan << std::endl;

    // Sets bullet to inactive after lifespan
    if (lifespan <= 0.0f) {
        isActive = false;
        // std::cout << "Bullet expired! Lifespan = " << lifespan << std::endl;
    }
}

bool Bullet::isActiveBullet() const {
    return isActive;
}

float Bullet::getRadius() const {
    return 0.1f;
}

//When refactoring i had some problems, GPT helped with this (commented faultfinding code)
void Bullet::updateBullets(
    float deltaTime,
    std::vector<std::shared_ptr<Bullet>>& bullets,
    std::shared_ptr<Scene>& scene) {

    for (auto it = bullets.begin(); it != bullets.end();) {
        auto& bullet = *it;
        bullet->update(deltaTime);

        //std::cout << "Before removal check: Lifespan = " << bullet->lifespan
        //         << ", isActive = " << bullet->isActiveBullet() << std::endl;

        if (!bullet->isActiveBullet()) {
            //std::cout << "Removing bullet with Lifespan = " << bullet->lifespan << std::endl;
            scene->remove(*bullet->getMesh());
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}
