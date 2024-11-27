#include "GameSystem/GameHUD.h"
#include "threepp/loaders/FontLoader.hpp"
#include <iostream>

GameHUD::GameHUD(const threepp::WindowSize& size) : hud_(size) {
    try {
        // Load the default font
        threepp::FontLoader fontLoader;
        const auto font = fontLoader.defaultFont();

        // Create TextGeometry options
        threepp::TextGeometry::Options opts(font, 15, 5);

        // Health text
        healthText_ = std::make_shared<threepp::Text2D>(opts, "Health: 100");
        healthText_->setColor(threepp::Color::green);
        hud_.add(*healthText_, threepp::HUD::Options()
                                  .setNormalizedPosition({0.0f, 1.0f}) // Top-left corner
                                  .setVerticalAlignment(threepp::HUD::VerticalAlignment::TOP)
                                  .setHorizontalAlignment(threepp::HUD::HorizontalAlignment::LEFT));

        // Score text
        scoreText_ = std::make_shared<threepp::Text2D>(opts, "Score: 0");
        scoreText_->setColor(threepp::Color::white);
        hud_.add(*scoreText_, threepp::HUD::Options()
                                  .setNormalizedPosition({0.0f, 0.95f}) // Below Health
                                  .setVerticalAlignment(threepp::HUD::VerticalAlignment::TOP)
                                  .setHorizontalAlignment(threepp::HUD::HorizontalAlignment::LEFT));

        // Time Alive text
        timeText_ = std::make_shared<threepp::Text2D>(opts, "Time Alive: 0");
        timeText_->setColor(threepp::Color::yellow);
        hud_.add(*timeText_, threepp::HUD::Options()
                                 .setNormalizedPosition({0.0f, 0.90f}) // Below Score
                                 .setVerticalAlignment(threepp::HUD::VerticalAlignment::TOP)
                                 .setHorizontalAlignment(threepp::HUD::HorizontalAlignment::LEFT));

        std::cout << "HUD initialized successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception initializing HUD: " << e.what() << std::endl;
    }
}

void GameHUD::updateHealth(int health) {
    healthText_->setText("Health: " + std::to_string(health));
}

void GameHUD::updateScore(int score) {
    scoreText_->setText("Score: " + std::to_string(score));
}

void GameHUD::updateTimeAlive(float timeAlive) {
    timeText_->setText("Time Alive: " + std::to_string(static_cast<int>(timeAlive)));
}

void GameHUD::render(threepp::GLRenderer& renderer) {
    try {
        renderer.autoClear = false; // Prevent clearing the render target
        hud_.apply(renderer);
        renderer.autoClear = true; // Reset autoClear for future renders
    } catch (const std::exception& e) {
        std::cerr << "Exception while rendering HUD: " << e.what() << std::endl;
    }
}
