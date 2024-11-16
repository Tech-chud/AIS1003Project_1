#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include "threepp/threepp.hpp"
#include "Sprites/Player.h"
#include "Sprites/Bullet.h"
#include <set>
#include <vector>

using namespace threepp;

class InputListener : public KeyListener, public MouseListener {
public:
    explicit InputListener(Scene& scene, Player& player, std::vector<std::shared_ptr<Bullet>>& bullets);

    void onKeyPressed(KeyEvent evt) override;
    void onKeyReleased(KeyEvent evt) override;
    void onMouseDown(int button, const Vector2& pos) override; // For testing only; can be removed later

    void updateActions(float deltaTime);

private:
    Scene& scene;
    Player& player;
    std::vector<std::shared_ptr<Bullet>>& bullets;
    bool addedPlayer;

    std::set<Key> keysPressed;
    std::set<Key> keysReleased;

    bool isKeyPressed(Key key) const;
    bool isKeyReleased(Key key) const;
    void shootBullet();
};

#endif // INPUTLISTENER_HPP
