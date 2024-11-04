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



    float left = -canvas.aspect() * 5;
    float right = canvas.aspect() * 5;
    float top = 5;
    float bottom = -5;
    auto camera = OrthographicCamera::create(left, right, top, bottom, 0.1f, 100);
    camera->position.z = 10;

    // List to store multiple asteroids
    // Smart pointer for "safe" management of memory preventing memory leaks
    std::vector<std::shared_ptr<Asteroid>> asteroids;


    Clock clock;

    // Create player object
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



    canvas.animate([&]() {
        float deltaTime = clock.getDelta();
        timeSinceLastSpawn += deltaTime;

        // Spawn asteroids via intervals
        if (timeSinceLastSpawn >= spawnInterval) {
            auto asteroid = Asteroid::spawnAsteroid(left, right, top, bottom, *scene);
            asteroids.push_back(asteroid);  // Store the asteroid in asteroid vector

            timeSinceLastSpawn = 0.0f;
            spawnInterval = RandomGen::randomFloat(1.0f, 3.0f);
        }

        // Update all asteroids
        for (auto& asteroid : asteroids) {
            asteroid->update(deltaTime); // Update the asteroid's position and behavior
            asteroid->CheckPosAndWrap(left, right, top, bottom); // Handles wrapping
        }

        // Update player actions based on input
        listener.updateActions(deltaTime);

        // Update player position and handle wrapping
        player.update(deltaTime);
        player.CheckPosAndWrap(left, right, top, bottom);

        renderer.render(*scene, *camera);
    });

    return 0;
}
