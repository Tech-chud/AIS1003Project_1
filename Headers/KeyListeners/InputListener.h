#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include "threepp/threepp.hpp"
#include "Sprites/Player.h"
#include "Sprites/Bullet.h"
#include <unordered_set>
#include <functional> // For std::function

using namespace threepp;

class InputListener : public KeyListener, public MouseListener {
public:
    InputListener(Scene& scene, Player& player, std::vector<std::shared_ptr<Bullet>>& bullets);

    void onKeyPressed(KeyEvent evt) override;
    void onKeyReleased(KeyEvent evt) override;
    void onMouseDown(int button, const Vector2& pos) override;

    void updateActions(float deltaTime);

    void setRestartCallback(std::function<void()> callback);

private:
    Scene& scene;
    Player& player;
    std::vector<std::shared_ptr<Bullet>>& bullets;

    std::unordered_set<Key> keysPressed;
    std::unordered_set<Key> keysReleased;

    bool addedPlayer;

    // Callback for restarting the game
    std::function<void()> onRestart;

    bool isKeyPressed(Key key) const;
    bool isKeyReleased(Key key) const;

    void shootBullet();
};

#endif // INPUTLISTENER_HPP
