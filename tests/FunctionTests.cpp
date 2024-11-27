#include "Collision/InelasticCollision.h"
#include "Sprites/Asteroid.h"
#include "Sprites/Bullet.h"
#include "threepp/threepp.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace threepp;

TEST_CASE("InelasticCollision correctly handles asteroid-bullet collisions", "[InelasticCollision]") {
    // Create a scene
    auto scene = Scene::create();

    // Create an asteroid and a bullet
    auto asteroid = std::make_shared<Asteroid>(Vector3(0, 0, 0), 1.0f, Color::gray);
    auto bullet = std::make_shared<Bullet>(Vector3(0, 0, 0), 0.0f, 10.0f, Color::yellow);

    // Add their meshes to the scene
    scene->add(asteroid->getMesh());
    scene->add(bullet->getMesh());

    // Ensure asteroid and bullet are in the scene initially
    REQUIRE(asteroid->getMesh()->parent == scene.get());
    REQUIRE(bullet->getMesh()->parent == scene.get());

    // Set up vectors for testing
    std::vector<std::shared_ptr<Asteroid>> asteroids = {asteroid};
    std::vector<std::shared_ptr<Bullet>> bullets = {bullet};

    int score = 0;
    float timeAlive = 5.0f; // Arbitrary value for testing
    float scoreMult = 0.1f;

    // Call the collision handler
    InelasticCollision::handleCollisions(asteroids, bullets, scene, score, timeAlive, scoreMult);

    // Assert that asteroid and bullet were removed from the scene
    REQUIRE(asteroids.empty());
    REQUIRE(bullets.empty());
    REQUIRE(asteroid->getMesh()->parent == nullptr);
    REQUIRE(bullet->getMesh()->parent == nullptr);

    // Verify the score calculation
    int expectedScore = static_cast<int>(1 + timeAlive * scoreMult);
    REQUIRE(score == expectedScore);
}
