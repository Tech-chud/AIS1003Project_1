#include "Sprites/Asteroid.h"
#include "Util/RandomGen.h"

// Default variables
float Asteroid::timeSinceLastSpawn = 0.0f;
float Asteroid::spawnInterval = RandomGen::randomFloat(2.0f, 10.0f);

// Constructor
Asteroid::Asteroid(const threepp::Vector3& position, float mass, const threepp::Color& color)
    : MovingObject(position, mass) {
    auto geometry = threepp::PlaneGeometry::create(1, 1);
    auto material = threepp::MeshBasicMaterial::create({{"color", color}});
    mesh_ = threepp::Mesh::create(geometry, material);
    mesh_->position.copy(position_);
}

// Update the asteroid
void Asteroid::update(float deltaTime) {
    applyPhysics(deltaTime);
    mesh_->rotation.z += deltaTime;
}

// Get the radius for collision detection
float Asteroid::getRadius() const {
    return 0.5f;
}

// Getter for velocity
const threepp::Vector3& Asteroid::getVelocity() const {
    return velocity_;
}

// Setter for velocity
void Asteroid::setVelocity(const threepp::Vector3& velocity) {
    velocity_ = velocity;
}

// Getter for mass
float Asteroid::getMass() const {
    return mass_;
}

// Initialize spawn timers
void Asteroid::initializeSpawnTimers() {
    timeSinceLastSpawn = 0.0f;
    spawnInterval = RandomGen::randomFloat(3.0f, 5.0f);
}

// Spawn a new asteroid
std::shared_ptr<Asteroid> Asteroid::spawnAsteroid(
    float left, float right, float top, float bottom, threepp::Scene& scene) {
    float xPos, yPos;

    int edge = RandomGen::randomInt(0, 3); // 0 = left, 1 = right, 2 = top, 3 = bottom
    const float k = 0.3f;
    switch (edge) {
        case 0:
            xPos = left - k;
            yPos = RandomGen::randomFloat(bottom, top);
            break;
        case 1:
            xPos = right + k;
            yPos = RandomGen::randomFloat(bottom, top);
            break;
        case 2:
            xPos = RandomGen::randomFloat(left, right);
            yPos = top + k;
            break;
        case 3:
            xPos = RandomGen::randomFloat(left, right);
            yPos = bottom - k;
            break;
    }

    auto asteroid = std::make_shared<Asteroid>(
        threepp::Vector3(xPos, yPos, 0), 1.0f, threepp::Color::gray);

    threepp::Vector3 velocity(RandomGen::randomFloat(-1, 1), RandomGen::randomFloat(-1, 1), 0);
    asteroid->setVelocity(velocity);

    scene.add(asteroid->getMesh());

    return asteroid;
}

// Update asteroids
void Asteroid::updateAsteroids(
    float deltaTime,
    float left,
    float right,
    float top,
    float bottom,
    std::vector<std::shared_ptr<Asteroid>>& asteroids,
    threepp::Scene& scene) {

    timeSinceLastSpawn += deltaTime;

    if (timeSinceLastSpawn >= spawnInterval && asteroids.size() < 200) { //TEMP MAX LIMIT FOR TESTING
        auto asteroid = spawnAsteroid(left, right, top, bottom, scene);
        asteroids.push_back(asteroid);

        const float DifficultyMult = 1.05;

        timeSinceLastSpawn = 0.0f;

        spawnInterval = RandomGen::randomFloat(2.0f*DifficultyMult, 10.0f*DifficultyMult); //new spawn rate
    }

    for (auto& asteroid : asteroids) {
        asteroid->update(deltaTime);
        asteroid->checkPosAndWrap(left, right, top, bottom);
    }
}
