//GPT was used for help here early on when it comes to scene and aspect ratios
#include "GameSystem/GameInit.h"
#include "GameSystem/GameHUD.h"
#include <iostream>
#include "Sprites/Player.h"

void GameInit::Init() {
    // Initialize the scene
    scene = Scene::create();
    scene->background = Color::black;

    // Set up the camera bounds
    left = -canvas.aspect() * 5;
    right = canvas.aspect() * 5;
    top = 5;
    bottom = -5;

    // Initialize the camera
    camera = OrthographicCamera::create(left, right, top, bottom, 0.1f, 100);
    camera->position.z = 10;

    // Handle window resizing
    canvas.onWindowResize([&](WindowSize size) {
        left = -size.aspect() * 5;
        right = size.aspect() * 5;
        camera->left = left;
        camera->right = right;
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });
}

Canvas& GameInit::getCanvas() {
    return canvas;
}

GLRenderer& GameInit::getRenderer() {
    return renderer;
}

std::shared_ptr<Scene>& GameInit::getScene() {
    return scene;
}

std::shared_ptr<OrthographicCamera>& GameInit::getCamera() {
    return camera;
}

void GameInit::getBounds(float& outLeft, float& outRight, float& outTop, float& outBottom) {
    outLeft = left;
    outRight = right;
    outTop = top;
    outBottom = bottom;
}

// Restart and refresh vectors
void GameInit::restart(
    int& score, int& health, float& timeAlive, bool& gameOver,
    std::vector<std::shared_ptr<Asteroid>>& asteroids,
    std::vector<std::shared_ptr<Bullet>>& bullets,
    Player& player, GameHUD& hud) {

    // Reset game state variables
    score = 0;
    health = 100;
    timeAlive = 0.0f;

    // Ensure gameOver is set to false to resume the game
    gameOver = false;

    // Clear existing asteroids and bullets
    for (auto& asteroid : asteroids) {
        scene->remove(*asteroid->getMesh());
    }
    asteroids.clear();

    for (auto& bullet : bullets) {
        scene->remove(*bullet->getMesh());
    }
    bullets.clear();

    // Reset player position and velocity
    player.setPosition(Vector3(0, 0, 0));
    player.setVelocity(Vector3(0, 0, 0));

    // Reset HUD
    hud.updateHealth(health);
    hud.updateScore(score);
    hud.updateTimeAlive(timeAlive);

    hud.setGameOverVisible(false); // Hide the "Game Over" text

    std::cout << "Game restarted successfully." << std::endl;
}


