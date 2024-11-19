#include "threepp/threepp.hpp"
#include "Sprites/Asteroid.h"
#include "Sprites/Player.h"
#include "Sprites/Bullet.h"
#include "KeyListeners/InputListener.h"
#include "Collision/BaseCollisionDetector.h"
#include "Util/RandomGen.h"
#include "Util/MovingObjects.h"
#include <vector>


using namespace threepp;

int main() {
    Clock clock;
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

    // Handle window resizing
    canvas.onWindowResize([&](WindowSize size) {
        camera->left = -size.aspect() * 5;
        camera->right = size.aspect() * 5;
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    // Asteroid list
    std::vector<std::shared_ptr<Asteroid> > asteroids;
    // Bullet List
    std::vector<std::shared_ptr<Bullet> > bullets;

    // Create player object
    Player player(Vector3(0, 0, 0), 1.0f, Color::white);
    scene->add(player.getMesh());

    Asteroid::initializeSpawnTimers();

    // Input Listeners
    InputListener listener(*scene, player, bullets);
    canvas.addKeyListener(listener);
    canvas.addMouseListener(listener);

    canvas.animate([&]() {
        float deltaTime = clock.getDelta();

        // Spawn asteroids
        Asteroid::handleAsteroidSpawning(deltaTime, left, right, top, bottom, asteroids, *scene);


        // Update all asteroids
        for (auto &asteroid: asteroids) {
            asteroid->update(deltaTime); // Update the asteroid's position and behavior
            asteroid->checkPosAndWrap(left, right, top, bottom); // Handles wrapping
        }

        // Update player actions
        listener.updateActions(deltaTime);

        // Update all bullets
        // Includes ChatGPT code
        for (auto it = bullets.begin(); it != bullets.end();) {
            auto &bullet = *it;
            bullet->update(deltaTime);

            // Remove inactive bullets
            if (!bullet->isActiveBullet()) {
                scene->remove(*bullet->getMesh());
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }


        //TEST ONLY GPT COPY [
        for (auto itA = asteroids.begin(); itA != asteroids.end();) {
            bool asteroidRemoved = false;
            for (auto itB = bullets.begin(); itB != bullets.end();) {
                if (BaseCollisionDetector::hasCollided(*itA, *itB)) {
                    // Handle collision by removing from the scene
                    scene->remove(*(*itA)->getMesh());
                    scene->remove(*(*itB)->getMesh());

                    // Erase bullet from vector and break the inner loop
                    itB = bullets.erase(itB);
                    asteroidRemoved = true;
                } else {
                    ++itB;
                }
            }


            // If the asteroid was hit, remove it from the vector
            if (asteroidRemoved) {
                itA = asteroids.erase(itA);
            } else {
                ++itA;
            }
        }

        // TEST END]

        // Update player position and handle wrapping
        player.update(deltaTime);
        player.checkPosAndWrap(left, right, top, bottom);

        renderer.render(*scene, *camera);
    });

    return 0;
}
