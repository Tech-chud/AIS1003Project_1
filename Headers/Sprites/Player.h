#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"

using namespace threepp;

class Player : public MovingObject {
public:
    // Constructor with initial position and color
    Player(const Vector3& position, float mass, const Color& color);

    // Rotate the player based on input, with dt
    void rotate(float direction, float deltaTime);

    // Apply thrust in the forward direction, adjusted for upward initial orientation
    void applyThrust(float deltaTime);

    // Update the player position
    void update(float deltaTime) override;

    // Getter for rotation angle
    float getRotationAngle() const;

    // Return "radius" of Player for collision detection
    float getRadius() const override;

private:
    float rotationAngle;
    float thrustPower;
    float maxSpeed;
    float rotationSpeed;
};

#endif // PLAYER_HPP
