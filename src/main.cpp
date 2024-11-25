#include "threepp/threepp.hpp"
#include "GameSystem/GameInit.h"
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

    GameInit::Init();

    // Retrieve initialized objects. Help from ChatGPT here early on for canvas and such
    Canvas& canvas = GameInit::getCanvas();
    GLRenderer& renderer = GameInit::getRenderer();
    std::shared_ptr<Scene>& scene = GameInit::getScene();
    std::shared_ptr<OrthographicCamera>& camera = GameInit::getCamera();

    // Retrieve camera bounds
    float left, right, top, bottom;
    GameInit::getBounds(left, right, top, bottom);

    Asteroid::initializeSpawnTimers();

    // Asteroid list
    std::vector<std::shared_ptr<Asteroid> > asteroids;
    // Bullet List
    std::vector<std::shared_ptr<Bullet> > bullets;

    // Create player object
    Player player(Vector3(0, 0, 0), 1.0f, Color::white);
    scene->add(player.getMesh());

    // Input Listeners
    InputListener listener(*scene, player, bullets);
    canvas.addKeyListener(listener);
    canvas.addMouseListener(listener);

    canvas.animate([&]() {
        float deltaTime = clock.getDelta();

        // Spawn, update, and wrap asteroids
        Asteroid::updateAsteroids(deltaTime, left, right, top, bottom, asteroids, *scene);

        // Update player actions
        listener.updateActions(deltaTime);

        // Update player actions
        listener.updateActions(deltaTime);

        // Update all bullets
        // Includes ChatGPT code
        for (auto it = bullets.begin(); it != bullets.end();) {
            auto &bullet = *it;
            bullet->update(deltaTime);

            // Remove inactive bullets based on lifespan
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
