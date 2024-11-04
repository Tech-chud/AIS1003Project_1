#include "threepp/threepp.hpp"
#include "Asteroid.h"
#include "RandomGen.h"
#include "MovingObjects.h"
#include "InputListener.h"
#include "Player.h"
#include <vector>



using namespace threepp;

int main() {

    Canvas canvas("2D Asteroids");
    GLRenderer renderer(canvas.size());


    auto scene = Scene::create();
    scene->background = Color::black;


    // Adjust view to match aspect ratio (allows window size change)
    float left = -canvas.aspect() * 5;
    float right = canvas.aspect() * 5;
    float top = 5;
    float bottom = -5;
    auto camera = OrthographicCamera::create(left, right, top, bottom, 0.1f, 100);
    camera->position.z = 10;

    // List to store multiple asteroids
    // Smart pointer for "safe" management of memory preventing memory leaks
    std::vector<std::shared_ptr<Asteroid>> asteroids;

    // Initialize clock
    Clock clock;

    // Create player object and add it to the scene
    Player player(Vector3(0, 0, 0), 1.0f, Color::white);
    scene->add(player.getMesh());

    // Variables for random asteroid spawning time intervals
    float timeSinceLastSpawn = 0.0f;
    float spawnInterval = RandomGen::randomFloat(2.0f, 10.0f);

    // Handle window resizing
    canvas.onWindowResize([&](WindowSize size) {
        camera->left = -size.aspect() * 5;
        camera->right = size.aspect() * 5;
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Input Listeners
    InputListener listener(*scene, player);
    canvas.addKeyListener(listener);
    canvas.addMouseListener(listener);


    // Animation loop
    canvas.animate([&]() {
        float deltaTime = clock.getDelta(); // Get time since the last frame
        timeSinceLastSpawn += deltaTime;    // Accumulate time since the last spawn

        // Check if it's time to spawn a new asteroid
        if (timeSinceLastSpawn >= spawnInterval) {
            auto asteroid = Asteroid::spawnAsteroid(left, right, top, bottom, *scene);
            asteroids.push_back(asteroid);  // Store the asteroid in asteroid vector

            timeSinceLastSpawn = 0.0f; // Reset the timer
            spawnInterval = RandomGen::randomFloat(1.0f, 3.0f);
        }

        // Update all asteroids
        for (auto& asteroid : asteroids) {
            asteroid->update(deltaTime); // Update the asteroid's position and behavior
            asteroid->CheckPosAndWrap(left, right, top, bottom); // Handles wrapping
        }

        // Update player actions based on input
        listener.updateActions();

        // Update player position and handle wrapping
        player.update(deltaTime);
        player.CheckPosAndWrap(left, right, top, bottom);

        renderer.render(*scene, *camera); // Pass scene and Camera objects to renderer.
    });

    return 0;
}
