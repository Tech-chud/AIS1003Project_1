#include "threepp/threepp.hpp"
#include "Asteroid.h"
#include "RandomGen.h"
#include "MovingObjects.h"
#include <vector>

using namespace threepp;

int main() {
    // Initialize canvas and renderer
    Canvas canvas("2D Asteroids");
    GLRenderer renderer(canvas.size());

    // Create a 2D scene
    auto scene = Scene::create();
    scene->background = Color::black; // Set background color for contrast

    // Set up an OrthographicCamera for 2D rendering
    float left = -canvas.aspect() * 5;  // Adjust view to match aspect ratio
    float right = canvas.aspect() * 5;
    float top = 5;
    float bottom = -5;
    auto camera = OrthographicCamera::create(left, right, top, bottom, 0.1f, 100);
    camera->position.z = 10; // Move the camera slightly away from the origin

    // List to store multiple asteroids
    // Smart pointer for "safe" management of memory
    // example; prevent memory leak from no longer used asteroids not actually being destroyed, no manual memory management.
    std::vector<std::shared_ptr<Asteroid>> asteroids;

    // Initialize a clock to track time for spawning
    Clock clock;

    // Variables for random spawning time intervals
    float timeSinceLastSpawn = 0.0f; // Time since the last asteroid was spawned
    float spawnInterval = RandomGen::randomFloat(2.0f, 10.0f); // Random interval for spawning (between 2 and 10 seconds)

    // Handle window resizing
    canvas.onWindowResize([&](WindowSize size) {
        camera->left = -size.aspect() * 5;
        camera->right = size.aspect() * 5;
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Animation loop
    canvas.animate([&]() {
        float deltaTime = clock.getDelta(); // Get time since the last frame
        timeSinceLastSpawn += deltaTime;    // Accumulate time since the last spawn

        // Check if it's time to spawn a new asteroid
        if (timeSinceLastSpawn >= spawnInterval) {
            auto asteroid = Asteroid::spawnAsteroid(left, right, top, bottom, *scene); // Spawn a new asteroid
            asteroids.push_back(asteroid);  // Store the asteroid in asteroid vector

            timeSinceLastSpawn = 0.0f; // Reset the timer
            spawnInterval = RandomGen::randomFloat(1.0f, 3.0f); // Set a new random interval
        }

        // Update all asteroids
        for (auto& asteroid : asteroids) {
            asteroid->update(deltaTime); // Update the asteroid's position and behavior
            asteroid->CheckPosAndWrap(left, right, top, bottom); // Handles wrapping
        }

        renderer.render(*scene, *camera); // Pass scene and Camera objects to renderer. (Dereferences the smart pointer)
    });

    return 0;
}
