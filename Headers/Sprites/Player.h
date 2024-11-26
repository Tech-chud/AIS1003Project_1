#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Util/MovingObjects.h"
#include "threepp/threepp.hpp"
#include <cmath>

using namespace threepp;

class Player : public MovingObject {
public:
    static std::shared_ptr<Player> create(const Vector3& position, float mass, const Color& color);

    Player(const Vector3& position, float mass, const Color& color);

    void rotate(float direction, float deltaTime);
    void applyThrust(float deltaTime);
    void update(float deltaTime);

    float getRotationAngle() const;
    float getRadius() const;

    Vector3 getVelocity() const;
    void setVelocity(const Vector3& velocity);

    float getMass() const;
    void setMass(float mass);

    void setColor(const Color& color); // Method to change the player's color

private:
    float rotationAngle;
    float thrustPower;
    float maxSpeed;
    float rotationSpeed;

    std::shared_ptr<MeshBasicMaterial> material_;
};

#endif // PLAYER_HPP
