#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include "threepp/threepp.hpp"
#include "Player.h"
#include <set>
#include <iostream>

using namespace threepp;

class InputListener : public KeyListener, public MouseListener {
public:
    explicit InputListener(Scene& scene, Player& player)
        : scene(scene), player(player), addedPlayer(true) {
        scene.add(player.getMesh());
    }

    // Handles key press events
    void onKeyPressed(KeyEvent evt) override {
        keysPressed.insert(evt.key);
        keysReleased.erase(evt.key);
    }

    // Handles key release events
    void onKeyReleased(KeyEvent evt) override {
        keysPressed.erase(evt.key);
        keysReleased.insert(evt.key);
    }

    // Handles mouse click events
    void onMouseDown(int button, const Vector2& pos) override {
        if (button == 0) { // Left mouse button
            std::cout << "Mouse pressed at position: " << pos.x << ", " << pos.y << std::endl;
        }
    }

    // Updates player actions based on currently pressed keys
    void updateActions() {
        // Handle rotation
        if (isKeyPressed(Key::A)) {
            player.rotate(0.05f); // Rotate left
        }
        if (isKeyPressed(Key::D)) {
            player.rotate(-0.05f); // Rotate right
        }

        // Handle thrust
        if (isKeyPressed(Key::W)) {
            player.applyThrust(); // Apply thrust forward
        }
    }

private:
    Scene& scene;
    Player& player;
    bool addedPlayer;
    std::set<Key> keysPressed;
    std::set<Key> keysReleased;

    // Checks if a specific key is currently pressed
    bool isKeyPressed(Key key) const {
        return keysPressed.find(key) != keysPressed.end();
    }

    // Checks if a specific key has been released
    bool isKeyReleased(Key key) const {
        return keysReleased.find(key) != keysReleased.end();
    }
};

#endif // INPUTLISTENER_HPP
