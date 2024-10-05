//
// Created by borga on 05/10/2024.
//

#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H
#include "threepp/threepp.hpp"

using namespace threepp;

class MovingObject {
public:
    // Constructor
    MovingObject(const Vector3& position, float mass, const Color& color)
        : position_(position), mass_(mass), velocity_(0, 0, 0), acceleration_(0, 0, 0) {

        // Create a 2D plane geometry and material
        geometry_ = PlaneGeometry::create(1, 1); // Example 2D plane
        material_ = MeshBasicMaterial::create({{"color", color}});
        mesh_ = Mesh::create(geometry_, material_);
        mesh_->position.copy(position_);
    }

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~MovingObject() = default;

    // Pure virtual function to update object (must be implemented by derived classes)
    virtual void update(float deltaTime) = 0;

    // Physics update for position based on velocity and acceleration
    virtual void applyPhysics(float deltaTime) {
        velocity_ += acceleration_ * deltaTime;
        position_ += velocity_ * deltaTime;
        mesh_->position.copy(position_); // Update mesh position
    }

    // Setters and getters for common attributes
    void setPosition(const Vector3& position) { position_ = position; }
    Vector3 getPosition() const { return position_; }

    void setVelocity(const Vector3& velocity) { velocity_ = velocity; }
    Vector3 getVelocity() const { return velocity_; }

    void setAcceleration(const Vector3& acceleration) { acceleration_ = acceleration; }
    Vector3 getAcceleration() const { return acceleration_; }

    void setMass(float mass) { mass_ = mass; }
    float getMass() const { return mass_; }

    // New method to get the mesh for adding to the scene
    std::shared_ptr<Mesh> getMesh() const { return mesh_; }

    // Render the object
    void render(GLRenderer& renderer, Camera& camera) {
        renderer.render(*mesh_, camera);
    }

protected:
    // Common attributes
    Vector3 position_;
    Vector3 velocity_;
    Vector3 acceleration_;
    float mass_;

    // Threepp attributes for rendering
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<MeshBasicMaterial> material_;
};



#endif //MOVINGOBJECTS_H
