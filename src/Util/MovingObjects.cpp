#include "Headers/Util/MovingObjects.h"

MovingObject::MovingObject(const Vector3& position, float mass)
    : position_(position), mass_(mass), velocity_(0, 0, 0), acceleration_(0, 0, 0) {}

void MovingObject::applyPhysics(float deltaTime) {
    position_.add(velocity_ * deltaTime);
    velocity_.add(acceleration_ * deltaTime);

    // Update the mesh's position
    if (mesh_) {
        mesh_->position.copy(position_);
    }
}

void MovingObject::checkAndWrap(float left, float right, float top, float bottom) {
    if (position_.x < left) {
        position_.x = right;
    } else if (position_.x > right) {
        position_.x = left;
    }

    if (position_.y > top) {
        position_.y = bottom;
    } else if (position_.y < bottom) {
        position_.y = top;
    }

    if (mesh_) {
        mesh_->position.copy(position_);
    }
}

std::shared_ptr<Mesh> MovingObject::getMesh() const {
    return mesh_;
}

Vector3 MovingObject::getPosition() const {
    return position_;
}

float MovingObject::getRadius() const {
    return 0.5f; // Default radius
}
