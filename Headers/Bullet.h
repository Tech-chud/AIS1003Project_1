//
// Created by borga on 09/11/2024.
//


#ifndef BULLET_H
#define BULLET_H

#include "MovingObjects.h"
#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet : public MovingObject {
public:
    // Constructor to initialize the bullet with a position, direction, speed, and color
    Bullet(const Vector3& position, float angle, float speed, const Color& color)
        : MovingObject(position, 0.1f), lifespan(3.0f) {


        auto geometry = CylinderGeometry::create(0.05f, 0.05f, 0.1f);
        auto material = MeshBasicMaterial::create({{"color", color}});


        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position_);

        // Calculate initial velocity based on angle and speed
        // Includes some help from ChatGPT
        velocity_ = Vector3(-std::sin(angle), std::cos(angle), 0) * speed;
    }

    // Update the bullet's position
    void update(float deltaTime) override {

        applyPhysics(deltaTime);

        // Lifespan
        lifespan -= deltaTime;

        // Remove after lifespan is over
        if (lifespan <= 1.0f) {
            isActive = false;
        }
    }

    // Check if the bullet is active (still within its lifespan)
    bool isActiveBullet() const {
        return isActive;
    }

private:
    float lifespan;
    bool isActive = true;
};

#endif // BULLET_HPP