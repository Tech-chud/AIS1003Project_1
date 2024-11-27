#ifndef GAMEHUD_HPP
#define GAMEHUD_HPP

#include "threepp/threepp.hpp"
#include <memory>

class GameHUD {
public:
    explicit GameHUD(const threepp::WindowSize& size);

    void updateScore(int score);
    void updateHealth(int health);
    void updateTime(float time);
    void render(threepp::GLRenderer& renderer);

private:
    threepp::HUD hud_;
    std::shared_ptr<threepp::Text2D> scoreText_;
    std::shared_ptr<threepp::Text2D> healthText_;
    std::shared_ptr<threepp::Text2D> timeText_;
};

#endif // GAMEHUD_HPP
