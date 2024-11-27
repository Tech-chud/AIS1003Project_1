#ifndef HUD_HPP
#define HUD_HPP

#include "threepp/threepp.hpp"
#include <memory>
#include <string>

class HUD {
public:
    HUD(const std::shared_ptr<threepp::Canvas>& canvas);

    void updateScore(int score);
    void updateHealth(int health);
    void updateTime(float timeAlive);

    void render();

private:
    std::shared_ptr<threepp::Canvas> canvas_;
    std::shared_ptr<threepp::Text> scoreText_;
    std::shared_ptr<threepp::Text> healthText_;
    std::shared_ptr<threepp::Text> timeText_;

    int score_;
    int health_;
    float timeAlive_;

    void updateTextElements();
};

#endif // HUD_HPP
