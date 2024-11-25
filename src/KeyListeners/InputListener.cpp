#include "KeyListeners/InputListener.h"
#include <iostream>

InputListener::InputListener(Scene& scene, Player& player, std::vector<std::shared_ptr<Bullet>>& bullets)
    : scene(scene), player(player), bullets(bullets), addedPlayer(true) {
    scene.add(player.getMesh());
}

void InputListener::onKeyPressed(KeyEvent evt) {
    keysPressed.insert(evt.key);
    keysReleased.erase(evt.key);
}

void InputListener::onKeyReleased(KeyEvent evt) {
    keysPressed.erase(evt.key);
    keysReleased.insert(evt.key);
}

// For testing; can be removed or adjusted as needed
void InputListener::onMouseDown(int button, const Vector2& pos) {
    if (button == 0) {
        std::cout << "Mouse pressed at position: " << pos.x << ", " << pos.y << std::endl;
    }
}

void InputListener::updateActions(float deltaTime) {
    // Handle rotation
    if (isKeyPressed(Key::A)) {
        player.rotate(1.0f, deltaTime);
    }
    if (isKeyPressed(Key::D)) {
        player.rotate(-1.0f, deltaTime);
    }

    // Handle thrust
    if (isKeyPressed(Key::W)) {
        player.applyThrust(deltaTime);
    }

    // Handle shooting
    if (isKeyReleased(Key::SPACE)) {
        shootBullet();
        keysReleased.erase(Key::SPACE);
    }
}

bool InputListener::isKeyPressed(Key key) const {
    return keysPressed.find(key) != keysPressed.end();
}

bool InputListener::isKeyReleased(Key key) const {
    return keysReleased.find(key) != keysReleased.end();
}

//When refactoring i had some problems, GPT helped with this (commented faultfinding code)
void InputListener::shootBullet() {
    auto bullet = std::make_shared<Bullet>(player.getPosition(), player.getRotationAngle(), 15.0f, Color::yellow);
    bullets.push_back(bullet);
    scene.add(bullet->getMesh());

    /*std::cout << "Bullet spawned! Total bullets: " << bullets.size() << std::endl;
    std::cout << "Bullet position: (" << bullet->getPosition().x << ", "
              << bullet->getPosition().y << ", "
              << bullet->getPosition().z << ")" << std::endl;*/
}
