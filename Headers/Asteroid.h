// mild use of GPT such as help for use of
// Arrow operator(->) , override{} and general questions about code.
//https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/
//https://en.cppreference.com/w/cpp/language/override


#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "MovingObjects.h"
#include "RandomGen.h"

class Asteroid : public MovingObject {
public:
    // Constructor for Asteroid
    Asteroid(const Vector3& position, float mass, const Color& color)
        : MovingObject(position, mass) {

        // Create asteroid-specific 2D plane geometry and material
        auto geometry = PlaneGeometry::create(1, 1); // Example 2D plane geometry
        auto material = MeshBasicMaterial::create({{"color", color}});

        // Create the mesh specific to Asteroid
        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position_); // Initialize position
    }

    // Implement the update method (this overrides the pure virtual method in MovingObject)
    void update(float deltaTime) override {
        // Apply physics for movement
        applyPhysics(deltaTime);
        // Apply rotation updating via dT
        mesh_->rotation.z += deltaTime;
        // Additional logic to wrap the asteroid around the screen will be handled outside due to virtual void problems...
    }

    // Static function to spawn asteroids at the edges of the screen
    static std::shared_ptr<Asteroid> spawnAsteroid(float left, float right, float top, float bottom, Scene& scene) {
        float xPos, yPos;

        // Randomly choose one of the 4 edges
        int edge = RandomGen::randomInt(0, 3);  // 0 = left, 1 = right, 2 = top, 3 = bottom

        switch (edge) {
            case 0: // Left edge
                xPos = left-0.3f;  // Fixed x position
                yPos = RandomGen::randomFloat(bottom, top);  // Random y position
                break;
            case 1: // Right edge
                xPos = right+0.3f;  // Fixed x position
                yPos = RandomGen::randomFloat(bottom, top);  // Random y position
                break;
            case 2: // Top edge
                xPos = RandomGen::randomFloat(left, right);  // Random x position
                yPos = top+0.3f;  // Fixed y position
                break;
            case 3: // Bottom edge
                xPos = RandomGen::randomFloat(left, right);  // Random x position
                yPos = bottom-0.3f;  // Fixed y position
                break;
        }

        // Create the asteroid at the chosen edge
        auto asteroid = std::make_shared<Asteroid>(Vector3(xPos, yPos, 0), 1.0f, Color::gray);

        // Set a random velocity for the asteroid
        Vector3 velocity(RandomGen::randomFloat(-1, 1), RandomGen::randomFloat(-2, 2), 0);
        asteroid->setVelocity(velocity);

        // Add asteroid to the scene
        scene.add(asteroid->getMesh());

        // Return the asteroid object
        return asteroid;
    }
};


#endif // ASTEROID_HPP
