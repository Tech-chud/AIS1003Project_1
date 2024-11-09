#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include "threepp/threepp.hpp"
#include "Player.h"
#include "Bullet.h"
#include <set>
#include <iostream>


using namespace threepp;

class InputListener : public KeyListener, public MouseListener {
public:
    explicit InputListener(Scene& scene, Player& player, std::vector<std::shared_ptr<Bullet>>& bullets)
        : scene(scene), player(player), bullets(bullets), addedPlayer(true) {
        scene.add(player.getMesh());
    }

    void onKeyPressed(KeyEvent evt) override {
        keysPressed.insert(evt.key);
        keysReleased.erase(evt.key);
    }

    void onKeyReleased(KeyEvent evt) override {
        keysPressed.erase(evt.key);
        keysReleased.insert(evt.key);
    }

    // Delete later for testing only
    void onMouseDown(int button, const Vector2& pos) override {
        if (button == 0) {
            std::cout << "Mouse pressed at position: " << pos.x << ", " << pos.y << std::endl;
        }
    }

    // Updates player actions
    void updateActions(float deltaTime) {
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

private:
    Scene& scene;
    Player& player;
    std::vector<std::shared_ptr<Bullet>>& bullets;
    bool addedPlayer;

    std::set<Key> keysPressed;
    std::set<Key> keysReleased;

    // Key press check
    bool isKeyPressed(Key key) const {
        return keysPressed.find(key) != keysPressed.end();
    }

    // Key release check
    bool isKeyReleased(Key key) const {
        return keysReleased.find(key) != keysReleased.end();
    }

    // Shoots a bullet from the player's current position and direction
    // Includes code from ChatGPT
    void shootBullet() {
        auto bullet = std::make_shared<Bullet>(player.getPosition(), player.getRotationAngle(), 15.0f, Color::yellow);
        bullets.push_back(bullet);
        scene.add(bullet->getMesh());
    }
};

#endif // INPUTLISTENER_HPP
