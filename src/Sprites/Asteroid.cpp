// mild use of GPT such as help for use of
// Arrow operator(->) , override{} and general questions about code.
//https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/
//https://en.cppreference.com/w/cpp/language/override

#include "Sprites/Asteroid.h"
#include "Util/RandomGen.h"

Asteroid::Asteroid(const Vector3& position, float mass, const Color& color)
    : MovingObject(position, mass) {

    // Create asteroid-specific 2D plane geometry and material
    auto geometry = PlaneGeometry::create(1, 1); // Example 2D plane geometry
    auto material = MeshBasicMaterial::create({{"color", color}});

    // Create the mesh specific to Asteroid
    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_); // Initialize position
}

void Asteroid::update(float deltaTime) {
    applyPhysics(deltaTime);
    mesh_->rotation.z += deltaTime;
}

std::shared_ptr<Asteroid> Asteroid::spawnAsteroid(float left, float right, float top, float bottom, Scene& scene) {
    float xPos, yPos;

    // Randomly choose one of the 4 edges
    int edge = RandomGen::randomInt(0, 3);  // 0 = left, 1 = right, 2 = top, 3 = bottom
    const float k = 0.3f; // Constant for slightly hidden spawns

    switch (edge) {
        case 0: // Left edge
            xPos = left - k;
            yPos = RandomGen::randomFloat(bottom, top);  // Random y position
            break;
        case 1: // Right edge
            xPos = right + k;
            yPos = RandomGen::randomFloat(bottom, top);  // Random y position
            break;
        case 2: // Top edge
            xPos = RandomGen::randomFloat(left, right);  // Random x position
            yPos = top + k;
            break;
        case 3: // Bottom edge
            xPos = RandomGen::randomFloat(left, right);  // Random x position
            yPos = bottom - k;
            break;
    }

    // Create the asteroid at the chosen edge
    auto asteroid = std::make_shared<Asteroid>(Vector3(xPos, yPos, 0), 1.0f, Color::gray);

    // Set a random velocity for the asteroid
    Vector3 velocity(RandomGen::randomFloat(-1, 1), RandomGen::randomFloat(-2, 2), 0);
    asteroid->setVelocity(velocity);

    // Add asteroid to the scene
    scene.add(asteroid->getMesh());

    return asteroid;
}

float Asteroid::getRadius() const {
    return 1.0f;
}
