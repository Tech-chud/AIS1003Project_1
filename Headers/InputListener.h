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


    void onKeyPressed(KeyEvent evt) override {
        keysPressed.insert(evt.key);
        keysReleased.erase(evt.key);
    }


    void onKeyReleased(KeyEvent evt) override {
        keysPressed.erase(evt.key);
        keysReleased.insert(evt.key);
    }


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
    }

private:
    Scene& scene;
    Player& player;
    bool addedPlayer;
    std::set<Key> keysPressed;
    std::set<Key> keysReleased;


    bool isKeyPressed(Key key) const {
        return keysPressed.find(key) != keysPressed.end();
    }


    bool isKeyReleased(Key key) const {
        return keysReleased.find(key) != keysReleased.end();
    }
};

#endif // INPUTLISTENER_HPP
