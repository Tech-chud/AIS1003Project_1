// This part of the code has heavy use of Chat GPT for now
// May edit later for less "GPT type code"

#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H
#include "threepp/threepp.hpp"


using namespace threepp;

class MovingObject {
public:
    // Constructor
    MovingObject(const Vector3& position, float mass);

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~MovingObject() = default;

    // Pure virtual function to update object (must be implemented by derived classes)
    virtual void update(float deltaTime) = 0;

    // Physics update of position using velocity and acceleration
    void applyPhysics(float deltaTime);

    // Method to wrap the object around the screen if it goes out of bounds
    void checkPosAndWrap(float left, float right, float top, float bottom);

    // Method to set the velocity of the object
    void setVelocity(const Vector3& velocity);

    // Getter for the mesh
    std::shared_ptr<Mesh> getMesh() const;

    // Getter for the position
    Vector3 getPosition() const;

    // Getter for the radius (for collision detection)
    virtual float getRadius() const;

protected:
    Vector3 position_;
    Vector3 velocity_;
    Vector3 acceleration_;
    float mass_;
    std::shared_ptr<Mesh> mesh_;
};



#endif //MOVINGOBJECTS_H
