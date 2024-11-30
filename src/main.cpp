#include "threepp/threepp.hpp"
#include "GameSystem/GameInit.h"
#include "GameSystem/GameHUD.h"
#include "Sprites/Asteroid.h"
#include "Sprites/Player.h"
#include "Sprites/Bullet.h"
#include "KeyListeners/InputListener.h"
#include "Collision/BaseCollisionDetector.h"
#include "Collision/InelasticCollision.h"
#include "Util/RandomGen.h"
#include "Util/MovingObjects.h"
#include <vector>
#include <iostream>
#include <Collision/ElasticCollision.h>


using namespace threepp;

int main() {
    Clock clock;

    GameInit::Init();

    // Retrieve initialized objects. Help from ChatGPT here early on for canvas and such
    Canvas &canvas = GameInit::getCanvas();
    GLRenderer &renderer = GameInit::getRenderer();
    std::shared_ptr<Scene> &scene = GameInit::getScene();
    std::shared_ptr<OrthographicCamera> &camera = GameInit::getCamera();

    // Retrieve camera bounds
    float left, right, top, bottom;
    GameInit::getBounds(left, right, top, bottom);


    GameHUD hud(canvas.size());

    // Set game settings
    int score = 0;
    int health = 100;
    float timeAlive = 0.0f;
    bool gameOver = false;

    Asteroid::initializeSpawnTimers();

    // Asteroid list
    std::vector<std::shared_ptr<Asteroid> > asteroids;
    // Bullet List
    std::vector<std::shared_ptr<Bullet> > bullets;

    // Create player object
    Player player(Vector3(0, 0, 0), 1.0f, Color::white);
    scene->add(player.getMesh());


    InputListener listener(*scene, player, bullets);
    canvas.addKeyListener(listener);
    canvas.addMouseListener(listener);

    // Reset pass Got some help from GPT on reset
    listener.setRestartCallback([&]() {
        GameInit::restart(score, health, timeAlive, gameOver, asteroids, bullets, player, hud);
    });


    const float scoreMult = 0.05f; // Destroying asteroids score also dependant on how long you survive
    const float damageMult = 2.0f; // Damage to player based on combined Velocity*damageMult

    canvas.animate([&]() {
        float deltaTime = clock.getDelta();

        // Input listener must be outside of game over state so reset is possible
        listener.updateActions(deltaTime)
        ;
        if (!gameOver) {
            timeAlive += deltaTime; // Increment time alive

            // Update HUD values
            hud.updateHealth(health);
            hud.updateScore(score);
            hud.updateTimeAlive(timeAlive);

            // Spawn, update, and wrap asteroids
            Asteroid::updateAsteroids(deltaTime, left, right, top, bottom, asteroids, *scene, timeAlive);

            // Update player actions
            listener.updateActions(deltaTime);

            // Update all bullets
            Bullet::updateBullets(deltaTime, bullets, scene);

            // Asteroid-player collisions
            ElasticCollision::handleAsteroidPlayerCollision(asteroids, player, scene, deltaTime, health, damageMult);

            // Collisions between bullets and asteroids
            InelasticCollision::handleCollisions(asteroids, bullets, scene, score, timeAlive, scoreMult);

            // Collisions between Asteroids
            ElasticCollision::handleAsteroidCollisions(asteroids);

            // Update player position and handle wrapping
            player.update(deltaTime);
            player.checkPosAndWrap(left, right, top, bottom);

            if (health <= 0) {
                gameOver = true;
                hud.setGameOverVisible(true);
            }
        }

        renderer.render(*scene, *camera);


        hud.render(renderer); //Do not put above renderer.render(scene,camera)
    });

    return 0;
}
