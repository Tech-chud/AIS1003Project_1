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

    // Initialize HUD
    GameHUD hud(canvas.size());

    // TEMP
    int score = 0; // Player score
    int health = 100; // Player health
    float timeAlive = 0.0f; // Time alive in seconds

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
        Bullet::updateBullets(deltaTime, bullets, scene);

        // Asteroid-player collisions
        ElasticCollision::handleAsteroidPlayerCollision(asteroids, player, scene, deltaTime);

        // Collisions between bullets and asteroids
        InelasticCollision::handleCollisions(asteroids, bullets, scene);

        // Collisions between Asteroids
        ElasticCollision::handleCollisions(asteroids);

        // Update player position and handle wrapping
        player.update(deltaTime);
        player.checkPosAndWrap(left, right, top, bottom);

        renderer.render(*scene, *camera);

        // Render HUD
        hud.render(renderer);
    });

    return 0;
}
