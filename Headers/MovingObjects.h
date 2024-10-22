//
// Created by borga on 05/10/2024.
// This part of the code has heavy use of Chat GPT for now, I had a "structure" made however the use of physics objects was foreign to me
// May edit later for less "GPT type code"

#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H
#include "threepp/threepp.hpp"

using namespace threepp;

class MovingObject {
public:
    // Constructor
    MovingObject(const Vector3& position, float mass)
        : position_(position), mass_(mass), velocity_(0, 0, 0), acceleration_(0, 0, 0) {}

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~MovingObject() = default;

    // Pure virtual function to update object (must be implemented by derived classes)
    virtual void update(float deltaTime) = 0;

    // Physics update for position based on velocity and acceleration
    virtual void applyPhysics(float deltaTime) {
        velocity_ += acceleration_ * deltaTime;
        position_ += velocity_ * deltaTime;

        if (mesh_) {
            mesh_->position.copy(position_); // Update mesh position
        }
    }

    //May make this more "object oriented" later, wrapping isnt Asteroid specific so a general wrapping check of objects is preferred
    //Player and bullets will allso wrap
    void CheckPosAndWrap(float left, float right, float top, float bottom) {
        // Check position and wrap opposite side left / right
        // Positions are edited with +/- a constant for more "seamless" wrapping
        if (position_.x < left-0.5f) {
            position_.x = right+0.5f;
        } else if (position_.x > right+0.5f) {
            position_.x = left-0.5f;
        }

        // Check position and wrap opposite side top / bottom
        if (position_.y > top+0.5f) {
            position_.y = bottom-0.5f;
        } else if (position_.y < bottom-0.5f) {
            position_.y = top+0.5f;
        }

        // Update position
        mesh_->position.copy(position_);
    }

    // Setters and getters for common attributes
    void setPosition(const Vector3& position) { position_ = position; }
    Vector3 getPosition() const { return position_; }

    void setVelocity(const Vector3& velocity) { velocity_ = velocity; }
    Vector3 getVelocity() const { return velocity_; }

    void setAcceleration(const Vector3& acceleration) { acceleration_ = acceleration; }
    Vector3 getAcceleration() const { return acceleration_; }

    //mass may be unused unless usefull for colision

    void setMass(float mass) { mass_ = mass; }
    float getMass() const { return mass_; }

    // Accessor for mesh (to be defined by derived class)
    std::shared_ptr<Mesh> getMesh() const { return mesh_; }

protected:
    // Common attributes
    Vector3 position_;
    Vector3 velocity_;
    Vector3 acceleration_;
    float mass_;

    // Mesh, to be initialized in derived classes
    std::shared_ptr<Mesh> mesh_;
};



#endif //MOVINGOBJECTS_H
