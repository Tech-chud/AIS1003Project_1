//GPT was used for help here early on when it comes to scene and aspect ratios

#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP

#include "threepp/threepp.hpp"
#include <memory>
#include <vector>
#include "Sprites/Asteroid.h"
#include "Sprites/Bullet.h"
#include "Sprites/Player.h"
#include "GameSystem/GameHUD.h"

using namespace threepp;

class GameInit {
public:
    static void Init();


    static Canvas& getCanvas();
    static GLRenderer& getRenderer();
    static std::shared_ptr<Scene>& getScene();
    static std::shared_ptr<OrthographicCamera>& getCamera();
    static void getBounds(float& left, float& right, float& top, float& bottom);

    static void restart(
        int& score, int& health, float& timeAlive, bool& gameOver,
        std::vector<std::shared_ptr<Asteroid>>& asteroids,
        std::vector<std::shared_ptr<Bullet>>& bullets,
        Player& player, GameHUD& hud);

private:
    static inline Canvas canvas{"2D Asteroids"};
    static inline GLRenderer renderer{canvas.size()};
    static inline std::shared_ptr<Scene> scene;
    static inline std::shared_ptr<OrthographicCamera> camera;
    static inline float left, right, top, bottom;
};

#endif // GAMEINIT_HPP
