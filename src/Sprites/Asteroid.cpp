#include "Sprites/Asteroid.h"
#include "Util/RandomGen.h"

// Initialize static variables
float Asteroid::timeSinceLastSpawn = 0.0f;
float Asteroid::spawnInterval = RandomGen::randomFloat(2.0f, 10.0f);

Asteroid::Asteroid(const Vector3& position, float mass, const Color& color)
    : MovingObject(position, mass) {
    auto geometry = PlaneGeometry::create(1, 1);
    auto material = MeshBasicMaterial::create({{"color", color}});
    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position_);
}

void Asteroid::update(float deltaTime) {
    applyPhysics(deltaTime);
    mesh_->rotation.z += deltaTime;
}

float Asteroid::getRadius() const {
    return 1.0f;
}

std::shared_ptr<Asteroid> Asteroid::spawnAsteroid(float left, float right, float top, float bottom, Scene& scene) {
    float xPos, yPos;
    int edge = RandomGen::randomInt(0, 3);
    const float k = 0.3f;

    switch (edge) {
        case 0: xPos = left - k; yPos = RandomGen::randomFloat(bottom, top); break;
        case 1: xPos = right + k; yPos = RandomGen::randomFloat(bottom, top); break;
        case 2: xPos = RandomGen::randomFloat(left, right); yPos = top + k; break;
        case 3: xPos = RandomGen::randomFloat(left, right); yPos = bottom - k; break;
    }

    auto asteroid = std::make_shared<Asteroid>(Vector3(xPos, yPos, 0), 1.0f, Color::gray);
    Vector3 velocity(RandomGen::randomFloat(-1, 1), RandomGen::randomFloat(-2, 2), 0);
    asteroid->setVelocity(velocity);
    scene.add(asteroid->getMesh());

    return asteroid;
}

void Asteroid::initializeSpawnTimers() {
    timeSinceLastSpawn = 0.0f;
    spawnInterval = RandomGen::randomFloat(2.0f, 10.0f);
}

void Asteroid::handleAsteroidSpawning(float deltaTime, float left, float right, float top, float bottom,
                                       std::vector<std::shared_ptr<Asteroid>>& asteroids, Scene& scene) {
    timeSinceLastSpawn += deltaTime;

    if (timeSinceLastSpawn >= spawnInterval && asteroids.size() < 20) {
        auto asteroid = spawnAsteroid(left, right, top, bottom, scene);
        asteroids.push_back(asteroid);

        timeSinceLastSpawn = 0.0f;
        spawnInterval = RandomGen::randomFloat(1.0f, 2.0f);
    }
}
